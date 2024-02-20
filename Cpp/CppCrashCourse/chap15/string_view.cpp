#include <string>
#include <string_view>
#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

TEST_CASE("String view")
{
    std::string_view sv("Hello");

    REQUIRE_FALSE(sv.empty());
    REQUIRE(sv.size() == 5);
    REQUIRE_FALSE(sv.data() == nullptr);

    REQUIRE(sv.compare("Hello") == 0);
    sv.remove_prefix(2);
    REQUIRE(sv == "llo");
    sv.remove_suffix(1);
    REQUIRE(sv == "ll");
}