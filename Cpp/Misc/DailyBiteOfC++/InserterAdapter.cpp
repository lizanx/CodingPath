#include <algorithm>
#include <cassert>
#include <list>
#include <print>
#include <vector>

int main()
{
    std::vector<int> src{1, 2, 3};
    std::list<int> dst{4};

    std::copy(src.cbegin(), src.cend(), std::back_inserter(dst));
    assert((dst == std::list<int>{4, 1, 2, 3}));

    std::copy(src.cbegin(), src.cend(), std::front_inserter(dst));
    assert((dst == std::list<int>{3, 2, 1, 4, 1, 2, 3}));
    // Compiler error: no member named 'push_front' in 'std::vector<int>'
    // std::vector<int> vec{};
    // std::copy(src.cbegin(), src.cend(), std::front_inserter(vec));

    std::copy(src.cbegin(), src.cend(), std::inserter(dst, std::next(dst.begin())));
    assert((dst == std::list<int>{3, 1, 2, 3, 2, 1, 4, 1, 2, 3}));

    return 0;
}
