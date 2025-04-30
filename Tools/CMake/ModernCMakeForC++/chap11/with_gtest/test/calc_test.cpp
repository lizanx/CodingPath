#include "calc.hpp"
#include <gtest/gtest.h>

class CalcTestSuite : public ::testing::Test
{
protected:
    Calculator _calc{};
};

TEST_F(CalcTestSuite, SumTwoIntegers)
{
    Calculator calc{};

    EXPECT_EQ(5, calc.Sum(2, 3));
}

TEST_F(CalcTestSuite, MultiplyTwoIntegers)
{
    Calculator calc{};

    EXPECT_EQ(12, calc.Multiply(4, 3));
}
