#include <algorithm>
#include <cassert>
#include <vector>

int main()
{
    int a{20}, b{30};
    auto &r1 = std::min(a, b);
    b = 20;
    // Both min and max are biased towards the first argument.
    auto &r2 = std::min(a, b);
    auto &r3 = std::max(a, b);
    assert(&r1 == &r2 && &r2 == &r3);

    a = 10;
    b = 5;
    auto [min, max] = std::minmax(a, b);
    assert(&min == &b && &max == &a);

    auto q = std::minmax(30, a);

    auto m = std::min({5, 2, 4, 3, 9});
    assert(m == 2);

    auto [i, j] = std::minmax({5, 2, 4, 3, 9});
    assert(i == 2);
    assert(j == 9);

    std::vector<int> vec{5, 2, 4, 3, 9};
    auto [x, y] = std::ranges::minmax(vec);
    assert(x == 2 && y == 9);

    return 0;
}
