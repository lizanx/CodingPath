#include "calc.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("SumTwoIntegers", "[calc]")
{
    Calculator calc{};

    CHECK(5 == calc.Sum(2, 3));
}

TEST_CASE("MultiplyTwoIntegers", "[calc]")
{
    Calculator calc{};

    CHECK(12 == calc.Multiply(4, 3));
}
