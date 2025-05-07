#include <iostream>
#include "calc/calc.hpp"
#include "calc/extended/ext_calc.hpp"

int main(int argc, char *argv[])
{
    Calculator calc{};
    std::cout << "2 + 1 = " << calc.Sum(2, 1) << "\n";

    ExtendedCalculator extCalc{};
    std::cout << "2 - 1 = " << extCalc.Sub(2, 1) << "\n";

    return 0;
}
