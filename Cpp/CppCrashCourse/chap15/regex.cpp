#include <string>
#include <regex>
#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

TEST_CASE("Regular expression")
{
    std::regex re{R"((\d{4}-)?(\d{7}))"}; // Telephone number: 0558-4437626
    std::string s1{"0558-4437626"};
    std::string s2{"4437626"};
    std::string s3{"0457=4437626"};
    std::string s4{"Phone number: 0558-4437626"};

    SECTION("Match")
    {
        std::smatch matchResult{};

        const auto s1Matched = std::regex_match(s1, matchResult, re);
        REQUIRE(s1Matched);
        REQUIRE(matchResult.size() == 3);
        REQUIRE(matchResult[0] == "0558-4437626");
        REQUIRE(matchResult[1] == "0558-");
        REQUIRE(matchResult[2] == "4437626");

        const auto s2Matched = std::regex_match(s2, matchResult, re);
        REQUIRE(s2Matched);
        REQUIRE(matchResult.size() == 3);
        REQUIRE(matchResult[0] == "4437626");
        REQUIRE(matchResult[1] == "");
        REQUIRE(matchResult[2] == "4437626");

        const auto s3Matched = std::regex_match(s3, matchResult, re);
        REQUIRE_FALSE(s3Matched);
    }

    SECTION("Search")
    {
        REQUIRE_FALSE(std::regex_match(s4, re));
        REQUIRE(std::regex_search(s4, re));
    }

    SECTION("Replace")
    {
        const auto result = std::regex_replace(s4, re, "***");

        REQUIRE(result == "Phone number: ***");
    }
}