#include <algorithm>
#include <cassert>
#include <print>
#include <vector>

int main()
{
    std::vector<int> data{1, 2, 3, 4, 5, 5, 5, 6, 7, 8, 9};

    auto lowerBound = std::lower_bound(data.begin(), data.end(), 5);
    assert(*lowerBound == 5);
    // Same as:
    lowerBound = std::partition_point(data.begin(), data.end(), [](int n)
                                      { return n < 5; });
    assert(*lowerBound == 5);

    auto upperBound = std::ranges::upper_bound(data, 5);
    assert(*upperBound == 6);
    // Same as:
    upperBound = std::ranges::partition_point(data, [](int n)
                                              { return !(n > 5); });
    assert(*upperBound == 6);

    // [begin, lowerBound) forms the subrange of elements lower than value(5)
    auto lower = std::ranges::subrange(data.begin(), lowerBound);
    std::println("lower: ");
    for (int n : lower)
        std::print("{} ", n);
    std::println();

    // [lowerBound, upperBound) forms the subrange of elements equal to value(5)
    auto equal = std::ranges::subrange(lowerBound, upperBound);
    std::println("equal: ");
    for (int n : equal)
        std::print("{} ", n);
    std::println();

    // [upperBound, end) forms the subrange of elements higher than value(5)
    auto high = std::ranges::subrange(upperBound, data.end());
    std::println("high: ");
    for (int n : high)
        std::print("{} ", n);
    std::println();

    return 0;
}
