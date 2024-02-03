#include <map>
#include <string>
#define CATCH_CONFIG_MAIN
#include "../catch.hpp"


TEST_CASE("std::map")
{
    using std::map;
    using std::string;

    map<string, int> m{};

    SECTION("Initialization")
    {
        REQUIRE(m.empty());

        auto m2{m}; // copy construct
        REQUIRE(m2.empty());

        m["price"] = 10;
        REQUIRE_FALSE(m.empty());
        auto m3{std::move(m)}; // move construct
        REQUIRE(m2.empty());
        REQUIRE_FALSE(m3.empty());
        REQUIRE(m3["price"] == 10);

        // Initializer list
        map<string, int> m4{
            {"price", 15},
            {"stock", 3},
        };
        REQUIRE_FALSE(m4.empty());
        REQUIRE(m4["price"] == 15);
        REQUIRE(m4["stock"] == 3);

        // Copy assignment via iterator
        map<string, int> m5(m4.begin(), m4.end());
        REQUIRE_FALSE(m5.empty());
        REQUIRE(m5["price"] == 15);
        REQUIRE(m5["stock"] == 3);
    }

    SECTION("Access elements")
    {
        REQUIRE(m.empty());

        // Non-existent element will be created by default when accessed via operator[]
        REQUIRE(m["price"] == 0);
        REQUIRE(m.size() == 1);

        REQUIRE(m.at("price") == 0);
        // Non-existent element will trigeer exception when accessedd via at()
        REQUIRE_THROWS_AS(m.at("stock"), std::out_of_range);
    }

    SECTION("Search elements")
    {
        m["price"] = 20;
        m["stock"] = 5;
        REQUIRE(m.size() == 2);
        REQUIRE(m.count("price") == 1);
        REQUIRE(m.find("stock") != m.end());
        REQUIRE(m.count("owner") == 0);
        REQUIRE(m.find("brand") == m.end());
        
        // Since C++20
        REQUIRE(m.contains("price"));
        REQUIRE_FALSE(m.contains("cost"));
    }

    SECTION("Modify elements")
    {
        m["price"] = 20;

        // Successful insertion of non-existent element
        auto [iter, inserted] = m.insert({"stock", 5});
        REQUIRE(inserted);
        REQUIRE(iter->first == "stock");
        REQUIRE(iter->second == 5);
        // Failed insertion of existent elemtn, returned iter is the existent element
        std::tie(iter, inserted) = m.insert({"price", 10});
        REQUIRE_FALSE(inserted);
        REQUIRE(iter->first == "price");
        REQUIRE(iter->second == 20);

        std::tie(iter, inserted) = m.insert_or_assign("price", 100);
        REQUIRE_FALSE(inserted); // not insertion, assignment
        REQUIRE(iter->first == "price");
        REQUIRE(iter->second == 100);

        m.erase(m.find("price"));
        REQUIRE_FALSE(m.contains("price"));

        m.clear();
        REQUIRE(m.empty());

        m.emplace("price", 150);
        REQUIRE(m.find("price") != m.end());
        bool emplaced;
        std::tie(iter, emplaced) = m.try_emplace("price", 30);
        REQUIRE_FALSE(emplaced);
        REQUIRE(iter->second == 150);
    }
}