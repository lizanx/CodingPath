#include <chrono>
#include <functional>
#include <future>
#include <iostream>
#include <random>
#include <vector>

namespace
{
    template <typename T>
    using IterType = typename std::vector<T>::iterator;

    template <typename T>
    IterType<T> FindSequential(IterType<T> begin, IterType<T> end, T target)
    {
        // return std::find_if(begin, end, predicate);
        return std::find(begin, end, target);
    }

    template <typename T>
    IterType<T> FindParallel(std::vector<T> &vec, T target)
    {
        std::vector<std::future<IterType<T>>> results{};

        constexpr size_t PARTITION_SIZE = 100000;
        for (size_t i{}; i < vec.size(); i += PARTITION_SIZE)
        {
            auto beginIter = vec.begin() + i;
            auto endIter = (i + PARTITION_SIZE < vec.size()) ? (beginIter + PARTITION_SIZE) : vec.end();
            results.push_back(std::async(
                FindSequential<T>,
                beginIter,
                endIter,
                target));
        }

        for (size_t i{}; i < results.size(); ++i)
        {
            auto iter = results[i].get();
            if (iter != vec.begin() + i * PARTITION_SIZE)
            {
                return iter;
            }
        }

        return vec.end();
    }
}

int main()
{
    std::cout << "Generating random numbers...\n";
    auto randomGenerator = std::bind(std::uniform_int_distribution{1ULL, 1'000'000'000'000ULL}, std::default_random_engine{});
    std::vector<unsigned long long> numbers(1'000'000'000);
    std::generate(numbers.begin(), numbers.end(), randomGenerator);

    unsigned long long target = 2'342'315'048ULL;

    std::cout << "=== Start Testing Parallel Find ===\n";
    auto parallelStartTimepoint = std::chrono::steady_clock::now();
    auto parallelResult = FindParallel(numbers, target);
    auto parallelTimeConsumption = std::chrono::steady_clock::now() - parallelStartTimepoint;
    std::cout << "ParallelFind consumes "
              << std::chrono::duration_cast<std::chrono::milliseconds>(parallelTimeConsumption).count()
              << "ms.\n\n";

    std::cout << "=== Start Testing Sequential Find ===\n";
    auto sequentialStartTimepoint = std::chrono::steady_clock::now();
    auto sequentialResult = FindSequential(numbers.begin(), numbers.end(), target);
    auto sequentialTimeConsumption = std::chrono::steady_clock::now() - sequentialStartTimepoint;
    std::cout << "SequentialFind consumes "
              << std::chrono::duration_cast<std::chrono::milliseconds>(sequentialTimeConsumption).count()
              << "ms.\n";
}
