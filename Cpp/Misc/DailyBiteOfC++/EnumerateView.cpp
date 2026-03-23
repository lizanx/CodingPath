#include <print>
#include <ranges>
#include <vector>

int main()
{
    std::vector<int> data{1, 2, 3, 4, 5, 6, 7};

    // Apply enumerate before other views to inject original index.
    constexpr auto before = std::views::enumerate | std::views::filter([](auto t)
                                                                       { return std::get<1>(t) % 2 == 0; });
    for (auto [index, value] : data | before)
    {
        std::println("data[{}] = {}", index, value);
    }

    std::println("\n");

    // Apply enumerate after other views to index the resulting range.
    constexpr auto after = std::views::filter([](int v)
                                              { return v % 2 == 0; }) |
                           std::views::enumerate;
    for (auto [index, value] : data | after)

    {
        std::println("data[{}] = {}", index, value);
    }

    return 0;
}
