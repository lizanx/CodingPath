#include <algorithm>
#include <cassert>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

namespace
{
    constexpr const int g_min{0};
    constexpr const int g_max{1000000000};

    int GetRandomInt(int lowerBound, int upperBound)
    {
        std::mt19937 engine{static_cast<unsigned long long>(std::chrono::system_clock::now().time_since_epoch().count())};
        std::uniform_int_distribution distribution{lowerBound, upperBound};
        return distribution(engine);
    }
}

int main()
{
    constexpr const std::size_t collectionSize{1000000};
    std::vector<int> v1{};
    v1.reserve(collectionSize);
    std::generate_n(std::back_inserter(v1), collectionSize, []
                    { return GetRandomInt(g_min, g_max); });
    auto v2 = v1;

    auto start = std::chrono::steady_clock::now();
    std::nth_element(std::begin(v1), std::begin(v1) + collectionSize / 2, std::end(v1));
    auto end = std::chrono::steady_clock::now();
    auto timeElapsed = end - start;
    std::cout << "nth_element: " << timeElapsed.count() / 1000000 << "ms\n";

    start = std::chrono::steady_clock::now();
    std::sort(std::begin(v2), std::end(v2));
    end = std::chrono::steady_clock::now();
    timeElapsed = end - start;
    std::cout << "sort: " << timeElapsed.count() / 1000000 << "ms\n";

    assert(v1[collectionSize / 2] == v2[collectionSize / 2]);
}
