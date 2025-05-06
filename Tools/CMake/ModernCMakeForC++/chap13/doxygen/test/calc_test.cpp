#include "calc.hpp"
#include <cstdlib>

void TestCalcSumTwoInts()
{
    Calculator calc{};

    if (calc.Sum(2, 2) != 4)
        std::exit(1);
}

void TestCalcMultiplyTwoInts()
{
    Calculator calc{};

    if (calc.Multiply(1, 3) != 3)
        std::exit(1);
}
