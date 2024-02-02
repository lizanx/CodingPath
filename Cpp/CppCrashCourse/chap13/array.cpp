#include <array>
#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

TEST_CASE("Get array status")
{
    std::array<int, 5> arr{1, 2, 3, 4, 5};

    REQUIRE(arr.size() == 5);
    REQUIRE(arr.empty() == false);
    REQUIRE(arr.begin() != arr.end());
    REQUIRE(arr.data() != nullptr);
    REQUIRE(*(arr.data()) == 1);
}

TEST_CASE("Access array elements")
{
    std::array<int, 5> arr{1, 2, 3, 4, 5};

    REQUIRE(arr.front() == 1);
    REQUIRE(arr.back() == 5);
    REQUIRE(arr[1] == 2);
    REQUIRE(arr.at(2) == 3);
    REQUIRE(std::get<3>(arr) == 4);
    REQUIRE_THROWS_AS(arr.at(5), std::out_of_range);
}

TEST_CASE("Manipulate array elements")
{
    std::array<int, 5> arr{1, 2, 3, 4, 5};
    
    arr.front() = 10;
    arr.back() = 50;
    REQUIRE(arr[0] == 10);
    REQUIRE(arr[4] == 50);

    arr.fill(0);
    for (const int &i : arr)
    {
        REQUIRE(i == 0);
    }
}