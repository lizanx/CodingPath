#include <queue>
#include <list>
#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

TEST_CASE("Queue operations")
{
    std::queue<int> q1{};
    q1.push(1);
    q1.emplace(2);
    REQUIRE(!q1.empty());
    REQUIRE(q1.size() == 2);
    REQUIRE(q1.front() == 1);
    REQUIRE(q1.back() == 2);
    q1.pop();
    REQUIRE(q1.size() == 1);
    REQUIRE(q1.front() == 2);
    REQUIRE(q1.back() == 2);

    std::list<int> l{1, 2, 3};
    std::queue<int, decltype(l)> q2(l);
    REQUIRE(!q2.empty());
    REQUIRE(q2.size() == 3);
    q2.pop();
    q2.push(4);
    q2.push(5);
    REQUIRE(q2.size() == 4);
    REQUIRE(q2.front() == 2);
    REQUIRE(q2.back() == 5);
    // Ensure that q2 copies data from l.
    REQUIRE(l.size() == 3);
    REQUIRE(l.front() == 1);
    REQUIRE(l.back() == 3);
}