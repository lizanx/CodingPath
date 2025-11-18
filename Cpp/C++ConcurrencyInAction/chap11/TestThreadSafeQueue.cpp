#include <cassert>
#include <chrono>
#include <condition_variable>
#include <future>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

namespace
{
    using std::mutex, std::lock_guard, std::unique_lock, std::condition_variable;
    using std::string, std::cout;
    using std::chrono::seconds;

    template <typename T>
    class ThreadSafeQueue
    {
    public:
        ThreadSafeQueue()
        {
        }

        ThreadSafeQueue(const ThreadSafeQueue &other)
        {
            lock_guard lck{other._queueMutex};
            _queue = other._queue;
        }

        ThreadSafeQueue &operator=(const ThreadSafeQueue &) = delete;

        void Push(T newValue)
        {
            {
                lock_guard lck{_queueMutex};
                _queue.push(newValue);
            }
            _queueCondVar.notify_one();
        }

        bool TryPop(T &value)
        {
            lock_guard lck{_queueMutex};
            if (_queue.empty())
                return false;
            value = _queue.front();
            _queue.pop();
            return true;
        }

        std::shared_ptr<T> TryPop()
        {
            lock_guard lck{_queueMutex};
            if (_queue.empty())
                return nullptr;
            auto result = std::make_shared<T>(_queue.front());
            _queue.pop();
            return result;
        }

        void WaitAndPop(T &value)
        {
            unique_lock lck{_queueMutex};
            _queueCondVar.wait(lck, [this]()
                               { return !_queue.empty(); });
            value = _queue.front();
            _queue.pop();
        }

        std::shared_ptr<T> WaitAndPop()
        {
            unique_lock lck{_queueMutex};
            _queueCondVar.wait(lck, [this]()
                               { return !_queue.empty(); });
            auto result = std::make_shared<T>(_queue.front());
            _queue.pop();
            return result;
        }

        bool empty() const
        {
            lock_guard lck{_queueMutex};
            return _queue.empty();
        }

    private:
        std::queue<T> _queue{};
        mutable mutex _queueMutex{};
        condition_variable _queueCondVar{};
    };

    void Producer(ThreadSafeQueue<int> &out, int secs)
    {
        int i{};
        while (true)
        {
            std::this_thread::sleep_for(seconds{secs});
            cout << "Thread[" << std::this_thread::get_id() << "] generating data\n";
            out.Push(i);
            ++i;
        }
    }

    void Consumer(ThreadSafeQueue<int> &in)
    {
        int data{};
        while (true)
        {
            in.WaitAndPop(data);
            cout << "\tThread[" << std::this_thread::get_id() << "] consumed data " << data << '\n';
        }
    }

    void TestConcurrentPushAndPopOnEmptyQueue()
    {
        ThreadSafeQueue<int> q{};
        std::promise<void> go{}, pushReady{}, popReady{};
        std::shared_future<void> ready{go.get_future()};
        std::future<void> pushDone{};
        std::future<int> popDone{};
        try
        {
            pushDone = std::async(std::launch::async, [&q, ready, &pushReady]()
                                  {
                pushReady.set_value();
                ready.wait();
                q.Push(42); });
            popDone = std::async(std::launch::async, [&q, ready, &popReady]()
                                 {
                popReady.set_value();
                ready.wait();
                int result{};
                q.WaitAndPop(result);
                return result; });
            pushReady.get_future().wait();
            popReady.get_future().wait();
            go.set_value();
            pushDone.get();
            assert(popDone.get() == 42);
            assert(q.empty());
        }
        catch (...)
        {
            go.set_value();
            throw;
        }
    }
}

int main(int argc, char *argv[])
{
    TestConcurrentPushAndPopOnEmptyQueue();
    return EXIT_SUCCESS;
}
