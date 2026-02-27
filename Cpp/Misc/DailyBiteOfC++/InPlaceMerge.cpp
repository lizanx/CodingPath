#include <algorithm>
#include <chrono>
#include <concepts>
#include <iostream>
#include <random>
#include <ranges>

namespace
{
    void MergeSort(std::ranges::random_access_range auto &rng)
    {
        if (rng.size() <= 1)
            return;

        auto mid = std::begin(rng) + rng.size() / 2;
        auto left = std::ranges::subrange{std::begin(rng), mid};
        auto right = std::ranges::subrange{mid, std::end(rng)};
        MergeSort(left);
        MergeSort(right);
        std::ranges::inplace_merge(rng, mid);
    }
}

int main()
{
    std::mt19937 eng{static_cast<unsigned long>(std::chrono::system_clock::now().time_since_epoch().count())};
    std::uniform_int_distribution distribution{0, 100};
    std::vector<int> vec(20);
    std::generate_n(std::begin(vec), vec.size(), [&eng, &distribution]
                    { return distribution(eng); });
    std::cout << "Before merge sort:\n\t";
    for (int n : vec)
        std::cout << n << " ";
    std::cout << '\n';

    MergeSort(vec);

    std::cout << "After merge sort:\n\t";
    for (int n : vec)
        std::cout << n << " ";
    std::cout << '\n';

    return 0;
}
