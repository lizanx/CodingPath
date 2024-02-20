#include <string>
#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

TEST_CASE("Strings")
{
    using std::string;

    string str{"HelloWorld"};

    SECTION("Construction")
    {
        string s1{};
        REQUIRE(s1.empty());

        string s2(3, 'a');
        REQUIRE(s2 == "aaa");

        string s3(str);
        REQUIRE(s3 == "HelloWorld");

        string s4(std::move(s3));
        REQUIRE(s4 == "HelloWorld");

        string s5("HelloWorld", 5, 5);
        REQUIRE(s5 == "World");

        string s6("HelloWorld", 2);
        REQUIRE(s6 == "He");

        string s6_2(str, 2);
        REQUIRE(s6_2 == "lloWorld");

        string s7(str, 2, 3);
        REQUIRE(s7 == "llo");

        string s8(str.cbegin(), str.cbegin() + 2);
        REQUIRE(s8 == "He");

        string s9("Hello\0World");
        REQUIRE(s9 == "Hello");

        using namespace std::string_literals;
        string s10("Hello\0World"s);
        REQUIRE(s10.size() == 11);
    }

    SECTION("Inner storage")
    {
        REQUIRE_FALSE(str.empty());
        REQUIRE(str.size() == 10);
        REQUIRE(str.length() == 10);
        REQUIRE(str.capacity() >= 10);
        str.reserve(20);
        REQUIRE(str == "HelloWorld");
        REQUIRE(str.capacity() >= 20);
    }

    SECTION("Access elements")
    {
        REQUIRE(str[0] == 'H');
        REQUIRE(str[1] == 'e');

        REQUIRE(str.front() == 'H');
        REQUIRE(str.back() == 'd');

        REQUIRE_FALSE(str.data() == nullptr);
        REQUIRE_FALSE(str.c_str() == nullptr);

        auto itr{str.begin()};
        REQUIRE(*itr == 'H');
        itr++;
        REQUIRE(*itr == 'e');

        REQUIRE_THROWS_AS(str.at(10), std::out_of_range);
    }

    SECTION("Comparation")
    {
        using namespace std::literals::string_literals;

        REQUIRE(str < "hello");
        REQUIRE(str < "hello"s);
        REQUIRE(str > "ABC");
        REQUIRE(str > "ABC"s);
        REQUIRE(str.compare("hello") < 0);
        REQUIRE(str.compare("hello"s) < 0);
        REQUIRE(str.compare("ABC") > 0);
        REQUIRE(str.compare("ABC"s) > 0);
        REQUIRE(str.compare("HelloWorld") == 0);
        REQUIRE(str.compare("HelloWorld"s) == 0);
    }

    SECTION("Modification")
    {
        str.push_back('e');
        REQUIRE(str == "HelloWorlde");

        str.append(2, 'a');
        REQUIRE(str == "HelloWorldeaa");

        str.append("goodbye");
        REQUIRE(str == "HelloWorldeaagoodbye");
        str.append("goodbye", 4);
        REQUIRE(str == "HelloWorldeaagoodbyegood");
        
        string other{"Complex C++"};

        str = "HelloWorld";
        str.append(other.cbegin(), other.cbegin() + 4);
        REQUIRE(str == "HelloWorldComp");

        str.pop_back();
        REQUIRE(str == "HelloWorldCom");

        str.clear();
        REQUIRE(str.empty());

        str = "HelloWorld";
        str.erase(5, 3);
        REQUIRE(str == "Hellold");

        str = "HelloWorld";
        str.erase(str.begin(), str.begin() + 5);
        REQUIRE(str == "World");

        str = "HelloWorld";
        str.replace(str.begin(), str.begin() + 5, "Nice");
        REQUIRE(str == "NiceWorld");

        str = "HelloWorld";
        str.replace(str.begin(), str.begin() + 5, other.begin(), other.end());
        REQUIRE(str == "Complex C++World");

        str = "HelloWorld";
        str.replace(5, 5, other);
        REQUIRE(str == "HelloComplex C++");

        str = "HelloWorld";
        str.resize(12, '-');
        REQUIRE(str == "HelloWorld--");
        str.resize(10);
        REQUIRE(str == "HelloWorld");

        str = "HelloWorld";
        REQUIRE(str.substr() == "HelloWorld");
        REQUIRE(str.substr(5) == "World");
        REQUIRE(str.substr(5, 2) == "Wo");
    }

    SECTION("Search element")
    {
        REQUIRE(str.find("ll") == 2);
        REQUIRE(str.find("he") == std::string::npos);
        REQUIRE(str.find('o') == 4);
        REQUIRE(str.rfind('o') == 6);

        REQUIRE(str.find_first_of("aeiou") == 1);
        REQUIRE(str.find_first_not_of("aeiou") == 0);

        REQUIRE(str.find_last_of("aeiou") == 6);
        REQUIRE(str.find_last_not_of("aeiou") == 9);
    }

    SECTION("Convert to/from numbers")
    {
        using namespace std::literals::string_literals;

        REQUIRE(std::to_string(123) == "123");

        REQUIRE(123 == std::stoi("123"s));
        REQUIRE(123.45 == Approx(std::stod("123.45"s)));
        size_t last_char{};
        REQUIRE(255 == std::stoi("0xff"s, &last_char, 16)); // hex conversion
    }
}