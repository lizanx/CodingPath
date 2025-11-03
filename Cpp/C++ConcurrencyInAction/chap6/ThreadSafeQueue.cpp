#include <atomic>
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <syncstream>
#include <thread>

namespace
{
    template <typename T>
    class ThreadSafeQueue
    {
    private:
        struct Node
        {
            std::shared_ptr<T> Data{};
            std::unique_ptr<Node> Next{};
        };
        std::mutex _headMutex{};
        std::unique_ptr<Node> _head{};
        std::mutex _tailMutex{};
        Node *_tail{};
        std::condition_variable _dataCv{};

        Node *GetTail();
        std::unique_ptr<Node> PopHead();
        std::unique_lock<std::mutex> WaitForData();
        std::unique_ptr<Node> WaitPopHead();
        std::unique_ptr<Node> WaitPopHead(T &value);
        std::unique_ptr<Node> TryPopHead();
        std::unique_ptr<Node> TryPopHead(T &value);

    public:
        ThreadSafeQueue();
        ThreadSafeQueue(const ThreadSafeQueue &) = delete;
        ThreadSafeQueue &operator=(const ThreadSafeQueue &) = delete;

        std::shared_ptr<T> TryPop();
        bool TryPop(T &value);
        std::shared_ptr<T> WaitAndPop();
        void WaitAndPop(T &value);
        void Push(T newValue);
        bool Empty();
    };

    template <typename T>
    ThreadSafeQueue<T>::Node *ThreadSafeQueue<T>::GetTail()
    {
        std::lock_guard lck{_tailMutex};
        return _tail;
    }

    template <typename T>
    std::unique_ptr<typename ThreadSafeQueue<T>::Node> ThreadSafeQueue<T>::PopHead()
    {
        auto tmp = std::move(_head);
        _head = std::move(tmp->Next);
        return tmp;
    }

    template <typename T>
    std::unique_lock<std::mutex> ThreadSafeQueue<T>::WaitForData()
    {
        std::unique_lock<std::mutex> lck{_headMutex};
        _dataCv.wait(lck, [this]()
                     { return _head.get() != GetTail(); });
        return std::move(lck);
    }

    template <typename T>
    std::unique_ptr<typename ThreadSafeQueue<T>::Node> ThreadSafeQueue<T>::WaitPopHead()
    {
        auto headLock = WaitForData();
        return PopHead();
    }

    template <typename T>
    std::unique_ptr<typename ThreadSafeQueue<T>::Node> ThreadSafeQueue<T>::WaitPopHead(T &value)
    {
        auto headLock = WaitForData();
        value = std::move(*(_head->Data));
        return PopHead();
    }

    template <typename T>
    std::unique_ptr<typename ThreadSafeQueue<T>::Node> ThreadSafeQueue<T>::TryPopHead()
    {
        std::lock_guard lck{_headMutex};
        if (_head.get() == GetTail())
            return nullptr;
        return PopHead();
    }

    template <typename T>
    std::unique_ptr<typename ThreadSafeQueue<T>::Node> ThreadSafeQueue<T>::TryPopHead(T &value)
    {
        std::lock_guard lck{_headMutex};
        if (_head.get() == GetTail())
            return nullptr;
        value = std::move(*(_head->Data));
        return PopHead();
    }

    template <typename T>
    ThreadSafeQueue<T>::ThreadSafeQueue() : _head{std::make_unique<Node>()}, _tail{_head.get()}
    {
    }

    template <typename T>
    std::shared_ptr<T> ThreadSafeQueue<T>::TryPop()
    {
        auto oldHead = TryPopHead();
        return oldHead ? oldHead->Data : nullptr;
    }

    template <typename T>
    bool ThreadSafeQueue<T>::TryPop(T &value)
    {
        auto oldHead = TryPopHead(value);
        return oldHead != nullptr;
    }

    template <typename T>
    std::shared_ptr<T> ThreadSafeQueue<T>::WaitAndPop()
    {
        auto headNode = WaitPopHead();
        return headNode->Data;
    }

    template <typename T>
    void ThreadSafeQueue<T>::WaitAndPop(T &value)
    {
        WaitPopHead(value);
    }

    template <typename T>
    void ThreadSafeQueue<T>::Push(T newValue)
    {
        auto newData = std::make_shared<T>(std::move(newValue));
        auto newTail = std::make_unique<Node>();
        auto rawNewTail = newTail.get();
        {
            std::lock_guard lck{_tailMutex};
            _tail->Data = std::move(newData);
            _tail->Next = std::move(newTail);
            _tail = rawNewTail;
        }
        _dataCv.notify_one();
    }

    template <typename T>
    bool ThreadSafeQueue<T>::Empty()
    {
        std::lock_guard lck{_headMutex};
        return _head.get() == GetTail();
    }
}

int main(int argc, char *argv[])
{
    using namespace std::chrono_literals;

    constexpr std::size_t DATA_COUNT = 100;
    std::atomic<int> cnt{};
    std::osyncstream oSyncStream{std::cout};
    auto producer = [&cnt, &oSyncStream](ThreadSafeQueue<int> &q)
    {
        for (std::size_t i{}; i < DATA_COUNT; ++i)
        {
            q.Push(++cnt);
            std::this_thread::sleep_for(5ms);
        }
        oSyncStream << "-> Producing done.\n";
    };
    constexpr int MAX_MISS_CNT = 500;
    auto consumer = [&oSyncStream](ThreadSafeQueue<int> &q, int id)
    {
        int missCnt{};
        while (true)
        {
            if (missCnt >= MAX_MISS_CNT)
            {
                oSyncStream << "->Exit consumer[" << id << "].\n";
                break;
            }
            auto data = q.TryPop();
            if (data)
            {
                oSyncStream << "Consumer[" << id << "]:\t" << *data << '\n';
                missCnt = 0;
            }
            else
            {
                ++missCnt;
                std::this_thread::sleep_for(1ms);
            }
        }
    };

    ThreadSafeQueue<int> q{};
    std::thread producerThread{producer, std::ref(q)};
    std::thread consumerThread1{consumer, std::ref(q), 1};
    std::thread consumerThread2{consumer, std::ref(q), 2};
    std::thread consumerThread3{consumer, std::ref(q), 3};
    std::thread consumerThread4{consumer, std::ref(q), 4};
    producerThread.join();
    consumerThread1.join();
    consumerThread2.join();
    consumerThread3.join();
    consumerThread4.join();
    oSyncStream << "=== Exit main ===\n";
    return 0;
}
