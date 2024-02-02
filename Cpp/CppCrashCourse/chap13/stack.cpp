#include <stack>
#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

TEST_CASE("Stack operations")
{
    std::stack<int> t1{};
    REQUIRE(t1.empty());
    t1.push(1);
    t1.push(2);
    t1.push(3);
    REQUIRE(!t1.empty());
    REQUIRE(t1.size() == 3);
    REQUIRE(t1.top() == 3);
    t1.top() = 4;
    REQUIRE(t1.size() == 3);
    REQUIRE(t1.top() == 4);
    t1.pop();
    t1.pop();
    REQUIRE(t1.size() == 1);
    REQUIRE(t1.top() == 1);

    // Use stack as wrapper of vector.
    std::vector<int> v{1, 2, 3};
    std::stack<int, decltype(v)> t2(v);
    REQUIRE(t2.size() == 3);
    REQUIRE(t2.top() == 3);
    t2.pop();
    t2.emplace(4);
    t2.emplace(5);
    REQUIRE(t2.size() == 4);
    REQUIRE(t2.top() == 5);
}