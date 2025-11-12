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
        constexpr unsigned long MAX_CHUNK_SIZE = 10000;
        if (length <= MAX_CHUNK_SIZE)
            return std::accumulate(begin, end, init);

        TIter mid = begin;
        std::advance(mid, length / 2);
        std::future<TValue> firstHalf = std::async(ParallelAccumulate<TIter, TValue>, begin, mid, init);
        TValue secondHalf = ParallelAccumulate<TIter, TValue>(mid, end, TValue{});
        TValue result = firstHalf.get() + secondHalf;

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
