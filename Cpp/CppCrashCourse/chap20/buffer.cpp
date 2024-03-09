#include <string>
#include <iostream>
#include <boost/asio.hpp>
#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

TEST_CASE("const buffer")
{
    boost::asio::const_buffer buf{ "Hello world", 11 };
    REQUIRE(buf.size() == 11);
    REQUIRE(buf.data());
    REQUIRE(*static_cast<const char*>(buf.data()) == 'H');
}

TEST_CASE("mutable buffer")
{
    std::string s{ "Hello world" };
    boost::asio::mutable_buffer buf{ s.data(), s.size() };
    REQUIRE(buf.size() == s.size());
    REQUIRE(buf.data() == s.data());
}

TEST_CASE("stream buffer")
{
    boost::asio::streambuf buf{};
    std::ostream os{ &buf };
    std::string s{ "Hello World" };
    os << s;
    std::istream is{ &buf };
    is >> s;
    REQUIRE(s == "Hello");
    is >> s;
    REQUIRE(s == "World");
}