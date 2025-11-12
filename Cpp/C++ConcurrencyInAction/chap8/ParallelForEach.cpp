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
    template <typename TIter, typename TFunc>
    void ParallelForEachV1(TIter begin, TIter end, TFunc fn)
    {
        constexpr unsigned long MAX_ELEMENT_CNT_PER_THREAD = 10000;
        auto length = std::distance(begin, end);
        if (length < 2 * MAX_ELEMENT_CNT_PER_THREAD)
        {
            std::for_each(begin, end, fn);
            return;
        }
        TIter mid = begin + length / 2;
        std::future<void> firstHalfResult = std::async(ParallelForEachV1<TIter, TFunc>, begin, mid, fn);
        ParallelForEachV1<TIter, TFunc>(mid, end, fn);
        firstHalfResult.get();
    }

    template <typename TIter, typename TFunc>
    void ParallelForEachV2(TIter begin, TIter end, TFunc fn)
    {
        constexpr unsigned long MIN_ELEMENT_CNT_PER_THREAD = 1000;
        const unsigned hwMaxThreads = std::thread::hardware_concurrency();
        auto length = std::distance(begin, end);
        unsigned maxThreads = (length + MIN_ELEMENT_CNT_PER_THREAD / 2) / MIN_ELEMENT_CNT_PER_THREAD;
        unsigned threadCnt = std::min(hwMaxThreads == 0 ? 2 : hwMaxThreads, maxThreads);
        std::vector<std::jthread> threads(threadCnt - 1);
        std::vector<std::future<void>> results(threadCnt - 1);
        const unsigned blockSize = length / threadCnt;
        TIter blockBegin = begin;
        for (unsigned i{}; i < threadCnt - 1; ++i)
        {
            TIter blockEnd = blockBegin;
            std::advance(blockEnd, blockSize);
            auto task = std::packaged_task<void(TIter, TIter, TFunc)>{
                [](TIter b, TIter e, TFunc f)
                {
                    std::for_each(b, e, f);
                }};
            results[i] = task.get_future();
            threads[i] = std::jthread(std::move(task), blockBegin, blockEnd, fn);
            blockBegin = blockEnd;
        }
        std::for_each(blockBegin, end, fn);
        for (std::future<void> &fut : results)
            fut.get();
    }
}

int main(int argc, char *argv[])
{
    auto nums = std::ranges::views::iota(0, 1000000000) | std::ranges::to<std::vector>();
    auto transformation = [](int &n)
    {
        n = n * 4 / 3;
    };

    // Single thread
    auto startTime = std::chrono::steady_clock::now();
    std::for_each(nums.begin(), nums.end(), transformation);
    auto timeElapsed = std::chrono::steady_clock::now() - startTime;
    std::cout << "Single thread time consumption: "
              << std::chrono::duration_cast<std::chrono::microseconds>(timeElapsed).count()
              << "us" << std::endl;

    // Parallel computing V1
    startTime = std::chrono::steady_clock::now();
    ParallelForEachV1(nums.begin(), nums.end(), transformation);
    timeElapsed = std::chrono::steady_clock::now() - startTime;
    std::cout << "Parallel V1 time consumption: "
              << std::chrono::duration_cast<std::chrono::microseconds>(timeElapsed).count()
              << "us" << std::endl;

    // Parallel computing V2
    startTime = std::chrono::steady_clock::now();
    ParallelForEachV2(nums.begin(), nums.end(), transformation);
    timeElapsed = std::chrono::steady_clock::now() - startTime;
    std::cout << "Parallel V2 time consumption: "
              << std::chrono::duration_cast<std::chrono::microseconds>(timeElapsed).count()
              << "us" << std::endl;
}
