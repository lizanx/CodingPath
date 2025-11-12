#include <algorithm>
#include <atomic>
#include <chrono>
#include <future>
#include <iostream>
#include <numeric>
#include <ranges>
#include <string>
#include <thread>

namespace
{
    template <typename TIter, typename TMatchType>
    TIter ParallelFindV1(TIter start, TIter end, TMatchType match)
    {
        struct FindElement
        {
            void operator()(TIter start, TIter end, TMatchType match, std::promise<TIter> &result, std::atomic<bool> &done)
            {
                try
                {
                    for (TIter it = start; it != end && !done.load(); ++it)
                    {
                        if (*it == match)
                        {
                            result.set_value(it);
                            done.store(true);
                            return;
                        }
                    }
                }
                catch (...)
                {
                    try
                    {
                        result.set_exception(std::current_exception());
                        done.store(true);
                    }
                    catch (...)
                    {
                        // If "set_exception" throws(another thread has already set result or exception),
                        // we simply discard the exception and exit this thread.
                    }
                }
            }
        };

        constexpr unsigned long MIN_ELEMENT_CNT_PER_THREAD = 1000;
        const unsigned hwMaxThreads = std::thread::hardware_concurrency();
        auto length = std::distance(start, end);
        const unsigned maxThreads = (length + MIN_ELEMENT_CNT_PER_THREAD / 2) / MIN_ELEMENT_CNT_PER_THREAD;
        const unsigned threadCnt = std::min(hwMaxThreads == 0 ? 2 : hwMaxThreads, maxThreads);
        const unsigned blockSize = length / threadCnt;

        std::promise<TIter> result{};
        std::atomic<bool> done{};
        TIter blockStart = start;
        {
            std::vector<std::jthread> threads(threadCnt - 1);
            for (unsigned i{}; i < threadCnt - 1; ++i)
            {
                TIter blockEnd = blockStart;
                std::advance(blockEnd, blockSize);
                threads[i] = std::jthread{FindElement{}, blockStart, blockEnd, match, std::ref(result), std::ref(done)};
                blockStart = blockEnd;
            }
        } // Upon exit, all threads are finished and joined.
        FindElement{}(blockStart, end, match, result, done);

        if (!done.load())
            return end;
        return result.get_future().get();
    }

    template <typename TIter, typename TMatchType>
    TIter ParallelFindV2Implementation(TIter start, TIter end, TMatchType match, std::atomic<bool> &done)
    {
        try
        {
            constexpr unsigned MAX_ELEMENT_CNT_PER_THREAD = 10000;
            unsigned length = std::distance(start, end);
            if (length <= 2 * MAX_ELEMENT_CNT_PER_THREAD)
            {
                for (TIter it = start; it != end && !done.load(); ++it)
                {
                    if (*it == match)
                    {
                        done.store(true);
                        return it;
                    }
                }
                return end;
            }

            TIter mid = start + length / 2;
            std::future<TIter> asyncResult = std::async(ParallelFindV2Implementation<TIter, TMatchType>, mid, end, match, std::ref(done));
            TIter directResult = ParallelFindV2Implementation(start, mid, match, done);
            return (directResult == mid) ? asyncResult.get() : directResult;
        }
        catch (...)
        {
            done.store(true);
            throw;
        }
    }

    template <typename TIter, typename TMatchType>
    TIter ParallelFindV2(TIter start, TIter end, TMatchType match)
    {
        std::atomic<bool> done{};
        return ParallelFindV2Implementation(start, end, match, done);
    }
}

int main(int argc, char *argv[])
{
    auto nums = std::ranges::views::iota(0, 1000000000) | std::ranges::to<std::vector>();
    constexpr int valueToFind{10000000};

    // Single thread
    auto startTime = std::chrono::steady_clock::now();
    auto result = std::find(nums.begin(), nums.end(), valueToFind);
    auto timeElapsed = std::chrono::steady_clock::now() - startTime;
    std::cout << "Single thread: "
              << "found = " << std::boolalpha << (result != nums.end())
              << ", time consumption = "
              << std::chrono::duration_cast<std::chrono::microseconds>(timeElapsed).count()
              << "us" << std::endl;

    // Parallel V1
    startTime = std::chrono::steady_clock::now();
    result = ParallelFindV1(nums.begin(), nums.end(), valueToFind);
    timeElapsed = std::chrono::steady_clock::now() - startTime;
    std::cout << "Parallel V1: "
              << "found = " << std::boolalpha << (result != nums.end())
              << ", time consumption = "
              << std::chrono::duration_cast<std::chrono::microseconds>(timeElapsed).count()
              << "us" << std::endl;

    // Parallel V2
    startTime = std::chrono::steady_clock::now();
    result = ParallelFindV2(nums.begin(), nums.end(), valueToFind);
    timeElapsed = std::chrono::steady_clock::now() - startTime;
    std::cout << "Parallel V2: "
              << "found = " << std::boolalpha << (result != nums.end())
              << ", time consumption = "
              << std::chrono::duration_cast<std::chrono::microseconds>(timeElapsed).count()
              << "us" << std::endl;
}
