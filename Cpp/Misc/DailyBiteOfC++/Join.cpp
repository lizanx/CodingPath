#include <algorithm>
#include <ranges>
#include <print>
#include <vector>

int main()
{
    std::vector<std::vector<int>> data{{1, 2, 3}, {4, 5}, {6, 7, 8, 9}};

    for (int n : data | std::views::join)
        std::print("{} ", n);

    std::println("\n\n");

    for (int n : data | std::views::filter([](const auto &rng)
                                           { return rng.size() > 2; }) |
                     std::views::join)
        std::print("{} ", n);
    std::println();

    return 0;
}
