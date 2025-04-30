#include <gtest/gtest.h>
#include "mocks/rng_mock.hpp"
#include "calc.hpp"

using namespace ::testing;

class CalcTestSuite : public Test
{
protected:
    MockRandomNumberGenerator _mockGen{};
    Calculator _calc{&_mockGen};
};

TEST_F(CalcTestSuite, SumTwoIntegers)
{
    EXPECT_EQ(5, _calc.Sum(2, 3));
}

TEST_F(CalcTestSuite, MultiplyTwoIntegers)
{
    EXPECT_EQ(12, _calc.Multiply(4, 3));
}

TEST_F(CalcTestSuite, AddRandomNumber)
{
    EXPECT_CALL(_mockGen, Get()).Times(1).WillOnce(Return(3));
    EXPECT_EQ(4, _calc.AddRandomNumber(1));
}
