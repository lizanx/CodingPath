#include <print>
#include <ranges>

int main()
{
    for (auto e : std::views::repeat(22) | std::views::take(5))
        std::println("{}", e);

    std::println();

    for (auto e : std::views::repeat(22, 5))
        std::println("{}", e);

    return 0;
}
