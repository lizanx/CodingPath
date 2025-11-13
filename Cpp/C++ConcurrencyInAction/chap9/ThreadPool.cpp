#include <algorithm>
#include <atomic>
#include <chrono>
#include <deque>
#include <future>
#include <iostream>
#include <memory>
#include <numeric>
#include <queue>
#include <ranges>
#include <string>
#include <thread>

namespace
{
    template <typename T>
    class ThreadSafeQueue
    {
    public:
        ThreadSafeQueue()
        {
        }

        ThreadSafeQueue(const ThreadSafeQueue &other)
        {
            std::lock_guard lck{other._queueMutex};
            _queue = other._queue;
        }

        ThreadSafeQueue &operator=(const ThreadSafeQueue &) = delete;

        void Push(T newValue)
        {
            {
                std::lock_guard lck{_queueMutex};
                _queue.push(std::move(newValue));
            }
            _queueCondVar.notify_one();
        }

        bool TryPop(T &value)
        {
            std::lock_guard lck{_queueMutex};
            if (_queue.empty())
                return false;
            value = std::move(_queue.front());
            _queue.pop();
            return true;
        }

        bool empty() const
        {
            std::lock_guard lck{_queueMutex};
            return _queue.empty();
        }

    private:
        std::queue<T> _queue{};
        std::mutex _queueMutex{};
        std::condition_variable _queueCondVar{};
    };

    class FunctionWrapper
    {
    public:
        template <typename TFunc>
        FunctionWrapper(TFunc &&f) : _impl{std::make_unique<Impl<TFunc>>(std::move(f))}
        {
        }

        FunctionWrapper() = default;

        FunctionWrapper(FunctionWrapper &&other) : _impl{std::move(other._impl)}
        {
        }
        FunctionWrapper &operator=(FunctionWrapper &&other)
        {
            _impl = std::move(other._impl);
            return *this;
        }

        FunctionWrapper(const FunctionWrapper &) = delete;
        FunctionWrapper &operator=(const FunctionWrapper &) = delete;

        void operator()()
        {
            _impl->Call();
        }

    private:
        struct ImplBase
        {
            virtual void Call() = 0;
            virtual ~ImplBase() {};
        };
        template <typename TFunc>
        struct Impl : ImplBase
        {
            TFunc Func;

            Impl(TFunc &&f) : Func{std::move(f)}
            {
            }

            void Call() override
            {
                Func();
            }
        };

        std::unique_ptr<ImplBase> _impl;
    };

    class WorkStealingQueue
    {
    public:
        WorkStealingQueue() = default;
        WorkStealingQueue(WorkStealingQueue &&) = delete;
        WorkStealingQueue &operator=(WorkStealingQueue &&) = delete;
        WorkStealingQueue(const WorkStealingQueue &) = delete;
        WorkStealingQueue &operator=(const WorkStealingQueue &) = delete;

        void Push(FunctionWrapper func)
        {
            std::lock_guard lck{_queueMutex};
            _queue.push_front(std::move(func));
        }

        bool Empty() const
        {
            std::lock_guard lck{_queueMutex};
            return _queue.empty();
        }

        // Pop from front, steal from back.

        bool TryPop(FunctionWrapper &func)
        {
            std::lock_guard lck{_queueMutex};
            if (_queue.empty())
                return false;
            func = std::move(_queue.front());
            _queue.pop_front();
            return true;
        }

        bool TrySteal(FunctionWrapper &func)
        {
            std::lock_guard lck{_queueMutex};
            if (_queue.empty())
                return false;
            func = std::move(_queue.back());
            _queue.pop_back();
            return true;
        }

    private:
        std::deque<FunctionWrapper> _queue{};
        mutable std::mutex _queueMutex{};
    };

    class ThreadPool
    {
    public:
        ThreadPool()
        {
            const unsigned threadCnt = std::jthread::hardware_concurrency();
            try
            {
                _queues.reserve(threadCnt);
                for (unsigned i{}; i < threadCnt; ++i)
                {
                    _queues.push_back(std::make_unique<WorkStealingQueue>());
                }

                _threads.reserve(threadCnt);
                for (unsigned i{}; i < threadCnt; ++i)
                {
                    _threads.push_back(std::jthread{&ThreadPool::WorkerThread, this, i});
                }
            }
            catch (...)
            {
                _done.store(true);
                throw;
            }
        }

        ~ThreadPool()
        {
            _done.store(true);
        }

        template <typename TFunc>
        std::future<typename std::invoke_result_t<TFunc>> Submit(TFunc func)
        {
            using ResultType = typename std::invoke_result_t<TFunc>;
            std::packaged_task<ResultType()> task{func};
            std::future<ResultType> result{task.get_future()};
            if (_localWorkQueue)
                _localWorkQueue->Push(std::move(task));
            else
                _poolWorkQueue.Push(std::move(task));
            return result;
        }

        void RunPendingTask()
        {
            TaskType task;
            if (PopTaskFromLocalQueue(task) || PopTaskFromPoolQueue(task) || PopTaskFromOtherThreadQueue(task))
            {
                task();
            }
            else
            {
                std::this_thread::yield();
            }
        }

    private:
        using TaskType = FunctionWrapper;
        std::atomic<bool> _done{};
        ThreadSafeQueue<TaskType> _poolWorkQueue{};
        std::vector<std::unique_ptr<WorkStealingQueue>> _queues{};
        std::vector<std::jthread> _threads{};

        static thread_local WorkStealingQueue *_localWorkQueue;
        static thread_local unsigned _index;

        void WorkerThread(unsigned index)
        {
            _index = index;
            _localWorkQueue = _queues[_index].get();
            while (!_done.load())
            {
                RunPendingTask();
            }
        }

        bool PopTaskFromLocalQueue(TaskType &task)
        {
            return _localWorkQueue && _localWorkQueue->TryPop(task);
        }

        bool PopTaskFromPoolQueue(TaskType &task)
        {
            return _poolWorkQueue.TryPop(task);
        }

        bool PopTaskFromOtherThreadQueue(TaskType &task)
        {
            for (unsigned i{}; i < _queues.size(); ++i)
            {
                // When stealing task from another thread, start from checking the adjacent next thread.
                // This can avoid the case that "all threads always steal tasks from the first thread first".
                const unsigned index = (_index + i + 1) % _queues.size();
                if (_queues[index]->TrySteal(task))
                {
                    return true;
                }
            }
            return false;
        }
    };

    thread_local WorkStealingQueue *ThreadPool::_localWorkQueue;
    thread_local unsigned ThreadPool::_index;
}

int main(int argc, char *argv[])
{
    std::vector<double> nums = std::ranges::views::iota(0, 10000000) | std::views::transform([](int i)
                                                                                             { return static_cast<double>(i); }) |
                               std::ranges::to<std::vector>();

    // Single thread
    {
        auto startTime = std::chrono::steady_clock::now();
        double average = std::accumulate(nums.begin(), nums.end(), 0.0) / nums.size();
        auto timeElapsed = std::chrono::steady_clock::now() - startTime;
        std::cout << "Single thread: "
                  << "average value =\t" << average
                  << ", time consumption =\t"
                  << std::chrono::duration_cast<std::chrono::microseconds>(timeElapsed).count()
                  << "us" << std::endl;
    }

    // Thread pool
    {
        auto startTime = std::chrono::steady_clock::now();

        auto blockSize = nums.size() / (std::jthread::hardware_concurrency() + 1);
        ThreadPool pool{};
        auto start = nums.begin();
        std::vector<std::future<double>> results(std::jthread::hardware_concurrency());
        for (unsigned i{}; i < std::jthread::hardware_concurrency(); ++i)
        {
            auto blockStart = start + i * blockSize;
            auto blockEnd = blockStart + blockSize;
            auto task =
                [blockStart, blockEnd, blockSize]() -> double
            {
                return std::accumulate(blockStart, blockEnd, 0.0) / blockSize;
            };
            // auto task = std::packaged_task<double()>{
            //     [blockStart, blockEnd, blockSize]()
            //     {
            //         return std::accumulate(blockStart, blockEnd, 0.0) / blockSize;
            //     }};
            // results[i] = task.get_future();
            results[i] = pool.Submit(task);
        }

        auto lastBlockStart = start + blockSize * std::jthread::hardware_concurrency();
        auto lastBlockElementCnt = std::distance(lastBlockStart, nums.end());
        double lastBlockAverage = std::accumulate(lastBlockStart, nums.end(), 0.0) / lastBlockElementCnt;

        double sum{lastBlockAverage};
        for (auto &result : results)
            sum += result.get();
        double average = sum / (results.size() + 1);

        auto timeElapsed = std::chrono::steady_clock::now() - startTime;
        std::cout << "Thread pool: "
                  << "average value =\t" << average
                  << ", time consumption =\t"
                  << std::chrono::duration_cast<std::chrono::microseconds>(timeElapsed).count()
                  << "us" << std::endl;
    }
}
