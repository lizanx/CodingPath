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
    template <typename TIter>
    void ParallelPartialsum(TIter start, TIter end)
    {
        using ValueType = TIter::value_type;

        struct ProcessChunk
        {
            void operator()(TIter start, TIter end, std::future<ValueType> *previousChunkEndValue, std::promise<ValueType> *endValue)
            {
                try
                {
                    TIter firstOfNextChunk = end;
                    ++firstOfNextChunk;
                    std::partial_sum(start, firstOfNextChunk, start);
                    if (previousChunkEndValue)
                    {
                        ValueType val = previousChunkEndValue->get();
                        *end += val;
                        if (endValue)
                        {
                            endValue->set_value(*end);
                        }
                        std::for_each(start, end, [val](ValueType &element)
                                      { element += val; });
                    }
                    else if (endValue) // First chunk
                    {
                        endValue->set_value(*end);
                    }
                }
                catch (...)
                {
                    if (endValue)
                    {
                        endValue->set_exception(std::current_exception());
                    }
                    else
                    {
                        throw;
                    }
                }
            }
        };

        constexpr unsigned long MIN_ELEMENT_CNT_PER_THREAD = 10000;
        const unsigned hwMaxThreads = std::thread::hardware_concurrency();
        auto length = std::distance(start, end);
        const unsigned maxThreads = (length + MIN_ELEMENT_CNT_PER_THREAD / 2) / MIN_ELEMENT_CNT_PER_THREAD;
        const unsigned threadCnt = std::min(hwMaxThreads == 0 ? 2 : hwMaxThreads, maxThreads);
        const unsigned chunkSize = length / threadCnt;

        std::vector<std::jthread> threads(threadCnt - 1);
        std::vector<std::promise<ValueType>> endValues(threadCnt - 1);
        std::vector<std::future<ValueType>> previousChunkEndValues{};
        previousChunkEndValues.reserve(threadCnt - 1);
        TIter chunkStart = start;
        for (unsigned i{}; i < threadCnt - 1; ++i)
        {
            TIter chunkEnd = chunkStart;
            std::advance(chunkEnd, chunkSize - 1);
            threads[i] = std::jthread{ProcessChunk{}, chunkStart, chunkEnd,
                                      (i == 0) ? nullptr : &previousChunkEndValues[i - 1], &endValues[i]};
            chunkStart = chunkEnd;
            ++chunkStart;
            previousChunkEndValues.push_back(endValues[i].get_future());
        }
        TIter finalElement = chunkStart;
        std::advance(finalElement, std::distance(chunkStart, end) - 1);
        ProcessChunk{}(chunkStart, finalElement, threadCnt > 1 ? &previousChunkEndValues.back() : nullptr, nullptr);
    }
}

int main(int argc, char *argv[])
{
    std::vector<unsigned long long> nums = std::ranges::views::iota(0ULL, 10000000ULL) | std::ranges::to<std::vector>();
    std::vector<unsigned long long> nums2(nums);

    // Single thread
    auto startTime = std::chrono::steady_clock::now();
    std::partial_sum(nums.begin(), nums.end(), nums.begin());
    auto timeElapsed = std::chrono::steady_clock::now() - startTime;
    std::cout << "Single thread: "
              << "last value =\t" << nums.back()
              << ", time consumption =\t"
              << std::chrono::duration_cast<std::chrono::microseconds>(timeElapsed).count()
              << "us" << std::endl;

    // Parallel
    startTime = std::chrono::steady_clock::now();
    ParallelPartialsum(nums2.begin(), nums2.end());
    timeElapsed = std::chrono::steady_clock::now() - startTime;
    std::cout << "Parallel V1: "
              << "last value =\t" << nums2.back()
              << ", time consumption =\t"
              << std::chrono::duration_cast<std::chrono::microseconds>(timeElapsed).count()
              << "us" << std::endl;
}
