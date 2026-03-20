#include <print>
#include <ranges>
#include <vector>

int main()
{
    std::vector<int> data{1, 2, 3, 4, 5, 6};

    std::println("<<< 1 >>>");
    for (std::tuple<int &, int &, int &> t : data | std::views::adjacent<3>)
    {
        std::println("Tuple: [{}, {}, {}]", std::get<0>(t), std::get<1>(t), std::get<2>(t));
    }

    std::println("<<< 2 >>>");
    for (auto [first, second, third] : data | std::views::adjacent<3>)
    {
        static_assert(std::is_same_v<decltype(first), int &>);
        std::println("first: {}, second: {}, thrid: {}",
                     first, second, third);
    }

    std::println("<<< 3 >>>");
    // std::views::adjacent<2> has an alias.
    for (auto [left, right] : data | std::views::pairwise)
    {
        std::println("left: {}, right: {}", left, right);
    }

    return 0;
}
