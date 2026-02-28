#include <algorithm>
#include <cassert>
#include <print>
#include <vector>
#include <list>

int main()
{
    std::vector<int> vec{1, 2, 3, 4, 5};
    std::list<int> lst{6, 7, 8, 9, 10};

    std::iter_swap(std::begin(vec), std::prev(std::end(vec)));
    assert(vec.front() == 5 && vec.back() == 1);

    std::iter_swap(std::begin(vec), std::begin(lst));
    assert(vec.front() == 6 && lst.front() == 5);

    return 0;
}
