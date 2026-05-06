#include <print>
#include <ranges>
#include <vector>

int main()
{
    std::vector<int> data{1, 2, 3, 4, 5, 6};

    for (int n : data | std::views::drop(2))
        std::print("{} ", n);
    std::println();

    for (int n : data | std::views::drop_while([](int x)
                                               { return x < 4; }))
        std::print("{} ", n);
    std::println();

    return 0;
}
