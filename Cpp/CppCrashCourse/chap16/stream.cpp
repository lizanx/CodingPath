#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <iterator>
#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

TEST_CASE("String stream")
{
    SECTION("Input string stream")
    {
        std::istringstream is{"Hello world"};
        std::string str{};
        is >> str;
        REQUIRE(str == "Hello");
        is >> str;
        REQUIRE(str == "world");
    }

    SECTION("Output string stream")
    {
        std::ostringstream os{};
        os << "Hello" << "World";
        REQUIRE(os.str() == "HelloWorld");
    }

    SECTION("I/O string stream")
    {
        std::stringstream ss{};
        ss << "Hello World";
        std::string str{};
        ss >> str;
        REQUIRE(str == "Hello");
        ss >> str;
        REQUIRE(str == "World");
    }
}

TEST_CASE("File stream")
{
    SECTION("Input file stream")
    {
        std::ifstream ifs{"numbers.txt"};
        REQUIRE(ifs.is_open());
        int num{};
        ifs >> num;
        REQUIRE(num == 1);
        ifs >> num;
        REQUIRE(num == -2);
        ifs >> num;
        REQUIRE(num == 3);
        REQUIRE(ifs.eof());
    }

    SECTION("Output file stream")
    {
        std::ofstream ofs{"output.txt"};
        for (int i{}; i < 3; i++)
        {
            ofs << i << ' ';
        }
        ofs.close();

        std::ifstream ifs{"output.txt"};
        REQUIRE(ifs.is_open());
        char content[7]{};
        ifs.read(content, 6);
        REQUIRE(strcmp(content, "0 1 2 ") == 0);
    }
}