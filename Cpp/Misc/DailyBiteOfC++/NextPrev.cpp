#include <cassert>
#include <list>
#include <iterator>
#include <vector>

int main()
{
    std::vector<int> vec{1, 2, 3, 4, 5};

    auto iter1 = std::prev(vec.end());
    assert(*iter1 == 5);

    // For random-access iterators, it's O(1) time.
    auto iter2 = std::next(vec.begin(), 2);
    assert(*iter2 == 3);

    std::list<int> lst{1, 2, 3, 4, 5};
    // Requires bi-directional iterator, and it's O(n) for non-random-access ones.
    auto iter3 = std::prev(lst.end(), 2);
    assert(*iter3 == 4);

    return 0;
}
