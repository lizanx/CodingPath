#include <algorithm>
#include <cassert>
#include <string>
#include <vector>

int main()
{
    std::vector<int> data{8, 2, 1, 7, 4, 5, 3, 6, 9};
    auto begin = data.begin();
    auto end = data.end();
    std::make_heap(begin, end);
    while (begin != end)
    {
        std::pop_heap(begin, end--);
    }
    assert((data == std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9}));

    std::vector<std::string> labels{"world", "bye", "fox", "lazy", "dog"};
    std::make_heap(labels.begin(), labels.end());
    std::pop_heap(labels.begin(), labels.end());
    labels.back()[0] = 'e';
    std::push_heap(labels.begin(), labels.end());
    std::sort_heap(labels.begin(), labels.end());
    assert((labels == std::vector<std::string>{"bye", "dog", "eorld", "fox", "lazy"}));

    return 0;
}
