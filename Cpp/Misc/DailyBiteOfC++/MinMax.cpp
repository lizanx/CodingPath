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

    {
        std::vector<int> data{1, 2, 3, 4, 5, 6};

        auto min = std::min_element(data.begin(), data.end());
        assert(*min == 1);

        auto max = std::max_element(data.begin(), data.end());
        assert(*max == 6);

        auto [x, y] = std::ranges::minmax(data);
        assert((x == 1 && y == 6));

        struct Element
        {
            int v;
        };
        std::vector<Element> elements{{2}, {1}, {4}, {5}, {3}};
        auto iter = std::ranges::min_element(elements, {}, &Element::v);
        assert(iter->v == 1);
    }

    return 0;
}
