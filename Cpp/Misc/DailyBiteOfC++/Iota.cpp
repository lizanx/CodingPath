#include <algorithm>
#include <cassert>
#include <numeric>
#include <ranges>
#include <vector>

int main()
{
    std::vector<int> data(5);
    std::iota(data.begin(), data.end(), 42);
    assert((data == std::vector<int>{42, 43, 44, 45, 46}));

    // One convenient use case is to generate an "indirect" container.
    std::vector<std::vector<int>::iterator> indirect(data.size());
    std::iota(indirect.begin(), indirect.end(), data.begin());
    std::sort(indirect.begin(), indirect.end(), [](auto &left, auto &right)
              { return *left > *right; });
    std::vector<int> reversed = indirect | std::views::transform([](auto iter)
                                                                 { return *iter; }) |
                                std::ranges::to<std::vector<int>>();
    assert((reversed == std::vector<int>{46, 45, 44, 43, 42}));

    auto v1 = std::views::iota(9, 12);
    auto v2 = std::views::iota(42);

    auto v3 = std::views::zip(std::views::iota(1), data);
}
