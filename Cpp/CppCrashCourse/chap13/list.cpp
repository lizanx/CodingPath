#include <list>
#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

TEST_CASE("List operations")
{
    std::list<int> l{1, 2, 3};
    REQUIRE(!l.empty());
    REQUIRE(l.size() == 3);
    REQUIRE(l.front() == 1);
    REQUIRE(l.back() == 3);

    l.push_back(4);
    l.push_front(5);
    REQUIRE(l.size() == 5);
    REQUIRE(l.front() == 5);
    REQUIRE(l.back() == 4);
    
    l.insert(l.begin(), 6);
    REQUIRE(l.front() == 6);
    l.pop_back();
    l.pop_front();
    REQUIRE(l.size() == 4);
    REQUIRE(l.front() == 5);
    REQUIRE(l.back() == 3);

    l.remove_if([](int x) { return x % 2 == 0; });
    REQUIRE(l.size() == 3);
    auto iter{ l.begin() };
    REQUIRE(*iter == 5);
    iter++;
    REQUIRE(*iter == 1);
    iter++;
    REQUIRE(*iter == 3);
    iter++;
    REQUIRE(iter == l.end());
}