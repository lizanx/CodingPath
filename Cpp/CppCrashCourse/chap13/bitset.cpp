#include <bitset>
#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

TEST_CASE("Operations of bitset")
{
    std::bitset<8> bs{};
    REQUIRE(bs.size() == 8);
    REQUIRE(!bs.all());
    REQUIRE(!bs.any());
    REQUIRE(bs.none());
    REQUIRE(!bs[0]);
    REQUIRE(!bs.test(7));
    REQUIRE_THROWS_AS(bs.test(8), std::out_of_range);

    bs.flip(0);
    bs.set(3);
    bs.set(5);
    REQUIRE(bs[0]);
    REQUIRE(bs[3]);
    REQUIRE(bs[5]);
    bs.reset(3);
    REQUIRE(!bs[3]);
    REQUIRE(!bs.all());
    REQUIRE(bs.any());
    REQUIRE(!bs.none());

    std::cout << bs << std::endl;
}