#include<deque>
#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

TEST_CASE("Deque")
{
    std::deque<int> d{1, 2, 3};
    REQUIRE(!d.empty());
    REQUIRE(d.size() == 3);
    REQUIRE(d.front() == 1);
    REQUIRE(d.back() == 3);
    REQUIRE(d[1] == 2);
    REQUIRE_THROWS_AS(d.at(3), std::out_of_range);

    auto middleIter{ d.begin() + 1 };
    d.pop_front();
    REQUIRE(*middleIter == 2);
    REQUIRE(d.size() == 2);
    d.erase(d.begin() + 1);
    REQUIRE(*middleIter == 2);
    REQUIRE(d.size() == 1);

    d.clear();
    REQUIRE(d.empty());

    d.assign({4, 5, 6});
    d.push_front(7);
    d.push_back(8);
    d.insert(d.begin(), 9);
    REQUIRE(d.size() == 6);
    REQUIRE(d[0] == 9);
    REQUIRE(d[1] == 7);
    REQUIRE(d[2] == 4);
    REQUIRE(d[3] == 5);
    REQUIRE(d[4] == 6);
    REQUIRE(d[5] == 8);
}