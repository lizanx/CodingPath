#include <algorithm>
#include <print>
#include <ranges>
#include <vector>

int main()
{
    std::vector<int> v1{1, 2, 3, 4, 5};
    std::vector<double> v2{9, 8, 7, 6};

    std::println("<<<<<  >>>>>");
    for (auto [a, b] : std::views::zip(v1, v2))
    {
        std::println("[{}, {}]", a, b);
    }

    std::println("<<<<<  >>>>>");
    for (std::tuple<int &, double &> e : std::views::zip(v1, v2))
    {
        std::println("[{}, {}]", std::get<0>(e), std::get<1>(e));
    }

    std::println("<<<<<  >>>>>");
    std::vector<std::string> v3{"label-1", "label-2", "label-3"};
    for (auto [a, b, c] : std::views::zip(v1, v2, v3))
    {
        std::println("[{}]: [{}, {}]", c, a, b);
    }

    std::println("<<<<<  >>>>>");
    // Since it's reference, you can modify the elements if possible.
    for (auto [a, b, c] : std::views::zip(v1, v2, v3))
    {
        std::println("[{}]: [{}, {}]  a+b={}", c, a, b, a + b);
        a = a + b;
    }
    std::println("v1:");
    for (int n : v1)
        std::print("{} ", n);
    std::println();

    return 0;
}
