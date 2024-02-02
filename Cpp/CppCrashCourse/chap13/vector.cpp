#include <vector>
#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

TEST_CASE("Vector initialization")
{
    std::vector<int> v1{1, 2, 3};
    REQUIRE(v1.front() == 1);
    REQUIRE(v1.back() == 3);

    std::vector<int> v2(3, 1);
    for (const int &i : v2)
    {
        REQUIRE(i == 1);
    }

    std::vector<int> v3{};
    v3.assign({3, 2, 1});
    REQUIRE(v3.front() == 3);
    REQUIRE(v3.back() == 1);

    std::vector<int> v4{};
    v4.assign(3, 1);
    for (const int &i : v4)
    {
        REQUIRE(i == 1);
    }
}

TEST_CASE("Access vector elements")
{
    std::vector<int> v{1, 2, 3};

    REQUIRE(v[0] == 1);
    REQUIRE(v.at(1) == 2);
    REQUIRE_THROWS_AS(v.at(3), std::out_of_range);
    REQUIRE(*v.begin() == v.front());
}

TEST_CASE("Variable size of vector")
{
    std::vector<int> v{};
    REQUIRE(v.size() == 0);

    v.reserve(10);
    REQUIRE(v.capacity() >= 10);
    REQUIRE(v.size() == 0);

    v.push_back(1);
    v.emplace_back(2);
    v.insert(v.begin(), 3);
    v.emplace(v.begin(), 4);
    REQUIRE(v.size() == 4);
    REQUIRE(v[0] == 4);
    REQUIRE(v[1] == 3);
    REQUIRE(v[2] == 1);
    REQUIRE(v[3] == 2);

    v.clear();
    REQUIRE(v.size() == 0);
    v.resize(5);
    REQUIRE(v.capacity() >= 10);
    v.assign({1, 2, 3});
    v.shrink_to_fit();
    REQUIRE(v.size() == 3);
}