#include <array>
#include <algorithm>
#include <cassert>
#include <numeric>

int main()
{
    using Array = std::array<int, 5>;
    Array a1{1, 2, 3, 4, 5};
    Array a2{1, 3, 5, 7, 9};
    Array outArray{};

    assert(std::accumulate(a1.cbegin(), a1.cend(), 0) == 15);
    assert(std::accumulate(a1.cbegin(), a1.cend(), 1, [](int a, int b)
                           { return a * b; }) == 120);

    assert(std::inner_product(a1.cbegin(), a1.cend(), a2.begin(), 0) == 95);

    std::partial_sum(a1.cbegin(), a1.cend(), outArray.begin());
    assert((outArray == Array{1, 3, 6, 10, 15}));

    std::adjacent_difference(a1.cbegin(), a1.cend(), outArray.begin());
    assert((outArray == Array{1, 1, 1, 1, 1}));
    std::adjacent_difference(a2.cbegin(), a2.cend(), outArray.begin());
    assert((outArray == Array{1, 2, 2, 2, 2}));

    std::iota(outArray.begin(), outArray.end(), 10);
    assert((outArray == Array{10, 11, 12, 13, 14}));
}
