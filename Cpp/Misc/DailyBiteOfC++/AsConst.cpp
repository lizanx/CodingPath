#include <cassert>
#include <list>
#include <print>
#include <ranges>
#include <vector>

int main()
{
    std::vector<int> randomAccessRng{1, 2, 3, 4, 5, 6};
    std::list<int> biDirectionalRng{1, 2, 3, 4, 5, 6};

    const auto v1 = randomAccessRng | std::views::drop(1);
    auto x1 = *v1.begin();
    assert(x1 == 2);
    *v1.begin() = 20;
    x1 = *v1.begin();
    assert(x1 == 20);

    const auto v2 = biDirectionalRng | std::views::drop(1);
    // Wouldn't compile: views::drop requires mutability to operate on non-random-access ranges.
    // auto x1 = *v2.begin();

    auto cview1 = randomAccessRng | std::views::as_const | std::views::drop(1);
    auto y1 = *cview1.begin();
    // *cview1.begin() = 2; // Cannot modify 'const int&`
    assert(y1 == 20);

    auto cview2 = biDirectionalRng | std::views::as_const | std::views::drop(1);
    auto y2 = *cview2.begin();
    assert(y2 == 2);

    return 0;
}
