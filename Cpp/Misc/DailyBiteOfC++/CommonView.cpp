#include <algorithm>
#include <cassert>
#include <numeric>
#include <ranges>

// Traditional [IterBegin, IterEnd) pair requires that both iters have the same type.
// While for ranges the bar is lifted - 'IterEnd' can be a sentinel type different from 'IterBegin'.
// To use ranges::views in traditional algorithms, you need 'std::views::common' for transformation.

int main()
{
    auto v = std::views::iota(1) | std::views::take(3);
    auto sum1 = std::ranges::fold_left_first(v, std::plus{});
    assert(sum1 == 6);
    // int sum2 = std::accumulate(v.begin(), v.end(), 0); // Cannot compile
    auto vCommon = v | std::views::common;
    int sum3 = std::accumulate(vCommon.begin(), vCommon.end(), 0);
    assert(sum3 == 6);

    return 0;
}
