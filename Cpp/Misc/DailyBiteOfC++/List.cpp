#include <cassert>
#include <forward_list>
#include <list>
#include <print>
#include <string_view>

namespace
{
    template <typename TContainer>
    void PrintContainer(const TContainer &container, std::string_view msg)
    {
        std::print("{}: ", msg);
        for (int n : container)
            std::print("{} ", n);
        std::println();
    }
}

int main()
{
    {
        std::list<int> data{1, 2, 3, 4, 5};
        std::list<int> other{6, 7, 8, 9};

        // linear operation
        auto iter = std::next(data.begin(), 2);
        // splice 1 element, O(1) operation
        other.splice(other.begin(), data, iter);
        PrintContainer(data, "data after splicing");
        PrintContainer(other, "other after splicing");
    }

    {
        std::forward_list<int> lst{5, 2, 1, 4, 3};
        // O(n) opeartion
        lst.sort();
        PrintContainer(lst, "After sort");
        // O(n) operation
        lst.reverse();
        PrintContainer(lst, "After reverse");

        lst.insert_after(lst.before_begin(), 42);
        PrintContainer(lst, "After inserting '42' to begin");

        lst.erase_after(lst.begin());
        PrintContainer(lst, "After removing begin");
    }

    return 0;
}
