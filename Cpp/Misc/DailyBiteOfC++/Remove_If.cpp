#include <algorithm>
#include <cassert>
#include <print>
#include <string>
#include <utility>
#include <vector>

namespace
{
    struct MoveOnlyObj
    {
        MoveOnlyObj(std::string value) : m_value{value} {}

        MoveOnlyObj(MoveOnlyObj &&other) : m_value{std::exchange(other.m_value, "empty")} {}

        MoveOnlyObj &operator=(MoveOnlyObj &&other)
        {
            m_value = std::exchange(other.m_value, "empty");
            return *this;
        }

        std::string m_value;
    };
}

int main()
{
    {
        std::vector<int> data{1, 2, 3, 4, 5};

        auto iter = std::remove(data.begin(), data.end(), 3);
        auto remainder = std::ranges::subrange(data.begin(), iter);
        std::print("After removing '3': ");
        for (int n : remainder)
            std::print("{} ", n);
        std::println();

        auto removed = std::ranges::remove_if(remainder, [](int n)
                                              { return n % 2 == 0; });
        auto oddNums = std::ranges::subrange(remainder.begin(), removed.begin());
        std::print("Left odd numbers: ");
        for (int n : oddNums)
            std::print("{} ", n);
        std::println();
    }

    // Move-only semantics
    {
        std::vector<MoveOnlyObj> moveSemantics{};
        moveSemantics.emplace_back("hello");
        moveSemantics.emplace_back("this");
        moveSemantics.emplace_back("is");
        moveSemantics.emplace_back("dog");
        auto removed = std::ranges::remove_if(moveSemantics, [](auto &e)
                                              { return e.m_value.length() > 4; });
        auto remained = std::ranges::subrange(moveSemantics.begin(), removed.begin());
        std::print("Remained move-only objects: ");
        for (const auto &e : remained)
            std::print("{} ", e.m_value);
        std::println();

        assert(removed.size() == 1);
        assert(removed.front().m_value == "empty");
    }

    return 0;
}
