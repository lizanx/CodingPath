#include <algorithm>
#include <cassert>
#include <forward_list>
#include <print>
#include <ranges>

int main()
{
    std::forward_list<int> data{1, 2, 3, 4, 5, 6, 7};

    {
        auto [iter, end] = std::ranges::find_last(data, 5);
        assert(end == data.end());
        if (iter != end)
        {
            std::println("Found last 5: data[{}] = {}", std::ranges::distance(data.begin(), iter), *iter);
        }
        else
        {
            std::println("Last 5 not found!");
        }

        auto res = std::ranges::find_last(data, 6);
        assert(res.end() == data.end());
        if (res)
        {
            std::println("Found last 6: data[{}] = {}", std::ranges::distance(data.begin(), res.begin()), *res.begin());
        }
        else
        {
            std::println("Last 6 not found!");
        }
    }
    std::println();
    {
        auto isEven = [](int n)
        {
            return n % 2 == 0;
        };
        auto res = std::ranges::find_last_if(data, isEven);
        assert(res.end() == data.end());
        if (!res.empty())
        {
            std::println("Found last even number: data[{}] = {}", std::ranges::distance(data.begin(), res.begin()), *res.begin());
        }
        else
        {
            std::println("Last even number not found!");
        }
    }
    std::println();
    {
        auto isOdd = [](int n)
        {
            return n % 2 != 0;
        };
        auto dataSubrange = std::views::counted(data.begin(), 5);
        auto res = std::ranges::find_last_if(dataSubrange, isOdd);
        assert(std::ranges::distance(dataSubrange.begin(), res.end()) == 5);
        if (res)
        {
            std::println("Found last odd number in first 5 numbers: {}", *res.begin());
        }
        else
        {
            std::println("Last odd number not found in first 5 numbers!");
        }
    }

    return 0;
}
