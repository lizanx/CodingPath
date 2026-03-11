#include <algorithm>
#include <cassert>
#include <iterator>
#include <vector>

int main()
{
    std::vector<int> v1{1, 2, 3, 4, 5, 6};

    std::vector<int> out1{};
    // std::copy offers a [iter, count] variant
    std::copy_n(v1.begin(), 3, std::back_inserter(out1));
    assert(out1.size() == 3);
    assert(out1.at(0) == 1);
    assert(out1.at(1) == 2);
    assert(out1.at(2) == 3);

    // For those algorithms which don't offer [iter, count] variant(only [begin iter, end iter] format),
    // use std::counted_iterator adapter.
    std::vector<int> out2{};
    std::ranges::copy(std::counted_iterator{v1.begin(), 3}, std::default_sentinel, std::back_inserter(out2));
    assert(out2.size() == 3);
    assert(out2.at(0) == 1);
    assert(out2.at(1) == 2);
    assert(out2.at(2) == 3);

    return 0;
}
