#include <algorithm>
#include <string>
#include <vector>
#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

using namespace std;

const vector<const string> languages{
    "C++",
    "C",
    "C#",
    "Python",
    "Go",
    "Kotlin",
    "Rust",
    "HTML",
    "Javascript"
};

TEST_CASE("all_of")
{
    REQUIRE(all_of(languages.cbegin(), languages.cend(),
            [](const auto& str){ return !str.empty(); }));
    REQUIRE_FALSE(all_of(languages.cbegin(), languages.cend(),
            [](const auto& str){ return str[0] == 'C'; }));
}

TEST_CASE("any_of")
{
    REQUIRE(any_of(languages.cbegin(), languages.cend(),
            [](const string& str){ return str.size() <= 1; }));
    REQUIRE_FALSE(any_of(languages.cbegin(), languages.cend(),
            [](const string& str){ return str.empty(); }));
}

TEST_CASE("none_of")
{
    REQUIRE(none_of(languages.cbegin(), languages.cend(),
            [](const string& str){ return str.empty(); }));
    REQUIRE_FALSE(none_of(languages.cbegin(), languages.cend(),
            [](const string& str){ return str.size() > 5; }));
}

TEST_CASE("for_each")
{
    size_t charCnt{};
    for_each(languages.cbegin(), languages.cend(),
            [&charCnt](const string& str){ charCnt += str.size(); });
    REQUIRE(charCnt == 38);
}

TEST_CASE("for_each_n")
{
    size_t charCnt{};
    for_each_n(languages.cbegin(), 3, [&charCnt](const string& str){ charCnt += str.size(); });
    REQUIRE(charCnt == 6);
}

TEST_CASE("find find_if find_if_not")
{
    auto itr = find(languages.cbegin(), languages.cend(), "C#");
    REQUIRE_FALSE(itr == languages.cend());
    REQUIRE(*itr == "C#");

    itr = find_if(languages.cbegin(), languages.cend(),
            [](const string& str){ return str.size() > 5; });
    REQUIRE_FALSE(itr == languages.cend());
    REQUIRE(*itr == "Python");

    itr = find_if_not(languages.cbegin(), languages.cend(),
            [](const string& str){
                return str.find('C') != string::npos;
            });
    REQUIRE_FALSE(itr == languages.cend());
    REQUIRE(*itr == "Python");
}

TEST_CASE("find_end")
{
    array<string, 2> searchedElements{ "Go", "Kotlin" };
    array<size_t, 2> searchedLengths{ 4, 4 };

    auto itr = find_end(languages.cbegin(), languages.cend(),
            searchedElements.cbegin(), searchedElements.cend());
    REQUIRE_FALSE(itr == languages.cend());
    REQUIRE(*itr == "Go");

    itr = find_end(languages.cbegin(), languages.cend(),
            searchedLengths.cbegin(), searchedLengths.cend(),
            [](const string& str, const size_t& size){ return str.size() == size; });
    REQUIRE_FALSE(itr == languages.cend());
    REQUIRE(*itr == "Rust");
}

TEST_CASE("find_first_of")
{
    array<string, 2> androidLanguages{ "Kotlin", "Java" };

    auto itr = find_first_of(languages.cbegin(), languages.cend(),
            androidLanguages.cbegin(), androidLanguages.cend());
    REQUIRE_FALSE(itr == languages.cend());
    REQUIRE(*itr == "Kotlin");

    array<string, 3> cFamilyLanguages{ "c#", "c++", "c" };
    itr = find_first_of(languages.cbegin(), languages.cend(),
            cFamilyLanguages.cbegin(), cFamilyLanguages.cend(),
            [](const string& s1, const string& s2){
                string lowercaseS1{ s1 };
                transform(lowercaseS1.begin(), lowercaseS1.end(), lowercaseS1.begin(), ::tolower);
                return lowercaseS1 == s2;
            });
    REQUIRE_FALSE(itr == languages.cend());
    REQUIRE(*itr == "C++");
}