#include <algorithm>
#include <cassert>
#include <iostream>
#include <valarray>

namespace
{
    bool CompareValarray(const std::valarray<int> &v1, const std::valarray<int> &v2)
    {
        return v1.size() == v2.size() && std::equal(std::cbegin(v1), std::cend(v1), std::cbegin(v2));
    }
}

int main()
{
    std::valarray v{1, 2, 3};

    v += 1;
    assert(CompareValarray(v, std::valarray<int>{2, 3, 4}));

    v *= 2;
    assert(CompareValarray(v, std::valarray<int>{4, 6, 8}));

    v = 0;
    assert(CompareValarray(v, std::valarray<int>{0, 0, 0}));

    std::valarray<int> v2(0, 3); // {0, 0, 0}
    assert(CompareValarray(v, v2));

    std::slice sl{1, 3, 2}; // start index from 1, 3 elements, stride is 2
    v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto sv = v[sl];
    sv = 0;
    assert(CompareValarray(v, std::valarray<int>{1, 0, 3, 0, 5, 0, 7, 8, 9}));
}
