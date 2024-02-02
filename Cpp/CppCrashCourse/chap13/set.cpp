#include <set>
#include <unordered_set>
#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

TEST_CASE("std::set")
{
    std::set<int> s{1, 2, 2, 3, 3};

    SECTION("Initialization")
    {
        REQUIRE(!s.empty());
        REQUIRE(s.size() == 3);
        auto iter{s.begin()};
        REQUIRE(*iter == 1);
        iter++;
        REQUIRE(*iter == 2);
        iter++;
        REQUIRE(*iter == 3);
        iter++;
        REQUIRE(iter == s.end());
    }

    SECTION("Search")
    {
        REQUIRE(s.find(1) != s.end());
        REQUIRE(s.find(3) != s.end());
        REQUIRE(s.find(5) == s.end());
        REQUIRE(s.count(2) == 1);
        REQUIRE(s.count(6) == 0);
    }

    SECTION("Modification")
    {
        s.insert(3);
        REQUIRE(s.size() == 3);
        s.insert(4);
        REQUIRE(s.size() == 4);
        REQUIRE(s.find(4) != s.end());

        s.clear();
        REQUIRE(s.empty());
        REQUIRE(s.size() == 0);
        s.emplace(7);
        s.emplace(5);
        s.insert(3);
        s.insert(9);
        REQUIRE(s.size() == 4);
        s.erase(3);
        REQUIRE(s.size() == 3);
        REQUIRE(s.find(3) == s.end());
        auto iter{s.begin()};
        REQUIRE(*iter == 5);
        iter++;
        REQUIRE(*iter == 7);
        iter++;
        REQUIRE(*iter == 9);
        iter++;
        REQUIRE(iter == s.end());
    }
}

TEST_CASE("std::multiset")
{
    std::multiset<int> ms{1, 1, 2, 3, 3};

    SECTION("Initialization")
    {
        REQUIRE(!ms.empty());
        REQUIRE(ms.size() == 5);
        auto iter{ms.begin()};
        REQUIRE(*iter == 1);
        iter++;
        REQUIRE(*iter == 1);
        iter++;
        REQUIRE(*iter == 2);
        iter++;
        REQUIRE(*iter == 3);
        iter++;
        REQUIRE(*iter == 3);
        iter++;
        REQUIRE(iter == ms.end());
    }

    SECTION("Search")
    {
        REQUIRE(ms.find(2) != ms.end());
        auto iter{ms.find(1)};
        REQUIRE(iter != ms.end());
        REQUIRE(*(++iter) == 1);
        
        REQUIRE(ms.count(1) == 2);
        REQUIRE(ms.count(2) == 1);
        REQUIRE(ms.count(3) == 2);
        REQUIRE(ms.count(4) == 0);
    }

    SECTION("Modification")
    {
        ms.insert(2);
        ms.insert(3);
        ms.insert(4);
        REQUIRE(ms.size() == 8);

        ms.erase(ms.find(3));
        REQUIRE(ms.size() == 7);
        REQUIRE(ms.count(3) == 2);

        ms.clear();
        REQUIRE(ms.empty());
        ms.emplace(5);
        ms.emplace(5);
        REQUIRE(ms.size() == 2);
    }
}

TEST_CASE("std::unordered_set")
{
    std::unordered_set<int> us{1, 2, 3, 3};

    SECTION("Initialization")
    {
        REQUIRE(!us.empty());
        REQUIRE(us.size() == 3);
    }

    SECTION("Search")
    {
        REQUIRE(us.count(1) == 1);
        REQUIRE(us.find(2) != us.end());
        REQUIRE(us.count(3) == 1);
        REQUIRE(us.find(4) == us.end());
    }

    SECTION("Modification")
    {
        us.insert(3);
        us.erase(2);
        REQUIRE(us.size() == 2);
        REQUIRE(us.find(1) != us.end());
        REQUIRE(us.find(2) == us.end());
        REQUIRE(us.find(3) != us.end());

        us.clear();
        REQUIRE(us.empty());
        us.emplace(1);
        us.emplace(1);
        us.emplace(2);
        REQUIRE(us.size() == 2);
    }
}