#include <algorithm>
#include <cassert>
#include <print>
#include <queue>
#include <ranges>
#include <vector>

int main()
{
    std::vector<int> data{1, 2, 3, 4, 5};

    auto c = std::views::counted(data.begin(), 3);
    assert(c.size() == 3);
    std::print("Count first 3: ");
    for (int n : c)
        std::print("{} ", n);
    std::println();

    std::deque<int> q{4, 3, 2, 5, 1};
    auto b = std::views::counted(q.begin(), 4);
    std::print("Count first 4: ");
    for (int n : b)
        std::print("{} ", n);
    std::println();

    return 0;
}
