#include <algorithm>
#include <chrono>
#include <future>
#include <iostream>
#include <numeric>
#include <ranges>
#include <string>
#include <thread>

namespace
{
    template <typename TIter, typename TValue>
    class BlockAccumulation
    {
    public:
        TValue operator()(TIter begin, TIter end)
        {
            return std::accumulate(begin, end, TValue{});
        }
    };

    template <typename TIter, typename TValue>
    auto ParallelAccumulate(TIter begin, TIter end, TValue init) -> TValue
    {
        const auto length = std::distance(begin, end);
        if (!length)
            return init;

        constexpr int MIN_ELEMENTS_PER_THREAD = 50;
        const int maxThreadsByElementsCnt = (length + MIN_ELEMENTS_PER_THREAD - 1) / MIN_ELEMENTS_PER_THREAD;
        const auto hwThreadCnt = std::thread::hardware_concurrency();
        const int threadCnt = std::min<unsigned int>(hwThreadCnt > 0 ? hwThreadCnt : 2, maxThreadsByElementsCnt);
        const auto blockSize = length / threadCnt;
        std::cout << "Thread cnt: " << threadCnt << ", block size: " << blockSize << '\n';

        std::vector<std::jthread> threads(threadCnt - 1);
        std::vector<std::future<TValue>> futures(threadCnt - 1);
        TIter blockBegin = begin;
        for (int i{}; i < (threadCnt - 1); ++i)
        {
            TIter blockEnd = blockBegin;
            std::advance(blockEnd, blockSize);
            auto task = std::packaged_task<TValue(TIter, TIter)>{BlockAccumulation<TIter, TValue>{}};
            futures[i] = task.get_future();
            threads[i] = std::jthread{std::move(task), blockBegin, blockEnd};
            blockBegin = blockEnd;
        }
        TValue result = init + BlockAccumulation<TIter, TValue>{}(blockBegin, end);
        for (unsigned i{}; i < threadCnt - 1; ++i)
            result += futures[i].get();

        return result;
    }
}

int main(int argc, char *argv[])
{
    auto nums = std::ranges::views::iota(0, 1000000000) | std::ranges::to<std::vector>();

    // Single thread
    auto startTime = std::chrono::steady_clock::now();
    auto result1 = std::accumulate(nums.begin(), nums.end(), 0ULL);
    auto timeElapsed = std::chrono::steady_clock::now() - startTime;
    std::cout << "Single thread result: " << result1 << '\t'
              << "Time elapsed: " << std::chrono::duration_cast<std::chrono::microseconds>(timeElapsed).count() << "us"
              << std::endl;

    // Parallel computing
    startTime = std::chrono::steady_clock::now();
    auto result2 = ParallelAccumulate(nums.begin(), nums.end(), 0ULL);
    timeElapsed = std::chrono::steady_clock::now() - startTime;
    std::cout << "Parallel computing result: " << result2 << '\t'
              << "Time elapsed: " << std::chrono::duration_cast<std::chrono::microseconds>(timeElapsed).count() << "us"
              << std::endl;
}
