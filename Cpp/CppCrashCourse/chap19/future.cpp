#include <string>
#include <future>
#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

using namespace std;

TEST_CASE("future")
{
    using namespace literals::string_literals;

    SECTION("valid")
    {
        auto f1 = async(launch::async, [](){ return "hello"s; });
        REQUIRE(f1.valid());

        future<string> f2{};
        REQUIRE_FALSE(f2.valid());
    }

    SECTION("get")
    {
        auto f = async([](){ return "hello"s; });
        REQUIRE(f.get() == "hello");

        auto fException = async([](){ throw runtime_error{ "Test exception" }; });
        REQUIRE_THROWS_AS(fException.get(), runtime_error);
    }

    SECTION("wait_for wait_until")
    {
        using namespace literals::chrono_literals;

        auto sleepy = async(launch::async, [](){ this_thread::sleep_for(100ms); });
        const auto notReadyYet = sleepy.wait_for(50ms);
        REQUIRE(notReadyYet == future_status::timeout);
        const auto ready = sleepy.wait_for(100ms);
        REQUIRE(ready == future_status::ready);
    }
}
