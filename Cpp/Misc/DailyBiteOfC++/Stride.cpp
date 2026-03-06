#include <print>
#include <ranges>
#include <string_view>
#include <vector>

int main()
{
    {
        using namespace std::literals;
        auto text = "helloworld"sv;
        for (char c : text | std::views::stride(2))
            std::print("{} ", c);
        std::println();
        for (char c : text | std::views::drop(1) | std::views::stride(2))
            std::print("{} ", c);
        std::println();
    }

    std::println("<-------------------------------->");

    {
        std::vector<int> data{1, 2, 3, 4, 5, 6, 7, 8, 9};
        // 3x3 2D array with stride of 3
        for (auto column : std::views::iota(0, 3))
        {
            for (auto e : data | std::views::drop(column) | std::views::stride(3))
                std::print("{} ", e);
            std::println();
        }
    }

    return 0;
}
