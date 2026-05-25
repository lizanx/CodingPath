#include <algorithm>
#include <map>
#include <print>
#include <vector>

namespace
{
    template <typename TContainer>
    void PrintContainer(const TContainer &container, std::string_view msg)
    {
        std::print("{}: ", msg);
        for (auto &n : container)
            std::print("{} ", n);
        std::println();
    }
}

int main()
{
    {
        std::vector<int> data{1, 2, 3, 4, 5};
        // Old way
        auto iter = std::remove(data.begin(), data.end(), 3);
        data.erase(iter, data.end());
        PrintContainer(data, "After removing '3' the old way");
        // New way
        std::erase(data, 4);
        PrintContainer(data, "After removing '4' the new way");
        size_t removedCnt = std::erase_if(data, [](int n)
                                          { return n % 2 == 0; });
        std::println("Count of removed even numbers: {}", removedCnt);
        PrintContainer(data, "After removing all even numbers");
    }

    {
        // Heterogeneous comparison
        std::vector<std::string> mixed{"hello", "this", "is", "dog"};
        std::erase(mixed, "hello");
        PrintContainer(mixed, "mixed after erasing");
    }

    {
        // unordered and associative containers only support std::erase_if
        std::map<int, int> map{{1, 2}, {2, 3}, {3, 4}};
        std::erase_if(map, [](auto &e)
                      { return e.first < 3; });
        PrintContainer(map, "Map");
    }
}
