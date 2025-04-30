#include "calc.hpp"
#include "rng_mt19937.hpp"
#include <iostream>

int StartProgram()
{
    auto generator = new MT19937RandomNumberGenerator{};

    Calculator calc{generator};
    int a{3}, b{5};
    std::cout << a << " + " << b << " = " << calc.Sum(a, b) << "\n"
              << a << " * " << b << " = " << calc.Multiply(a, b) << "\n";
    //   << a << " + Random Number = " << calc.AddRandomNumber(a) << "\n";

    delete generator;
    return 0;
}
