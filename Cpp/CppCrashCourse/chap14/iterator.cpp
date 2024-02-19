#include <iostream>
#include <vector>
#include <iterator>
#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

TEST_CASE("Iterator usage")
{
    std::vector<int> vec{
        1, 2, 3,
        4, 5, 6,
        7, 8, 9
    };

    SECTION("Random access iterator")
    {
        auto iter{vec.begin()};
        REQUIRE(iter[0] == 1);
        REQUIRE(iter[3] == 4);
        REQUIRE(*(iter + 6) == 7);
        iter += 4;
        REQUIRE(iter[-2] == 3);
        REQUIRE(*(iter - 3) == 2);
    }

    SECTION("Iterator helper functions")
    {
        auto iter{vec.begin()};
        std::advance(iter, 2);
        REQUIRE(*iter == 3);

        auto iter2 = std::prev(iter);
        REQUIRE(*iter2 == 2);
        auto iter3 = std::prev(iter, 2);
        REQUIRE(*iter3 == 1);

        auto iter4 = std::next(iter);
        REQUIRE(*iter4 == 4);
        auto iter5 = std::next(iter, 2);
        REQUIRE(*iter5 == 5);

        REQUIRE(std::distance(iter, iter4) == 1);
        REQUIRE(std::distance(iter, iter5) == 2);
        REQUIRE(std::distance(iter, iter2) == -1);
        REQUIRE(std::distance(iter, iter3) == -2);

        std::iter_swap(vec.begin(), vec.begin() + 1);
        REQUIRE(vec[0] == 2);
        REQUIRE(vec[1] == 1);
    }

    SECTION("Move iterators")
    {
        std::vector<int> vec2(std::make_move_iterator(vec.begin()),
                std::make_move_iterator(vec.end()));
        REQUIRE(vec2.size() == 9);
        for (size_t i{}; i < 9; i++)
        {
            REQUIRE(vec2[i] == i + 1);
        }
    }

    SECTION("Reverse iterators")
    {
        std::vector<int> vec2(vec.crbegin(), vec.crend());
        REQUIRE(vec2.size() == 9);
        for (size_t i{}; i < 9; i++)
        {
            REQUIRE(vec2[i] == 9 - i);
        }

        std::vector<int> vec3(std::make_reverse_iterator(vec.end()),
                std::make_reverse_iterator(vec.begin()));
        REQUIRE(vec3.size() == 9);
        for (size_t i{}; i < 9; i++)
        {
            REQUIRE(vec3[i] == 9 - i);
        }
    }
}