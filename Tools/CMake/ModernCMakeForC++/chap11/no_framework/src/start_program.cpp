#include "calc.hpp"
#include <iostream>

int StartProgram(int argc, char *argv[])
{
    Calculator calc{};
    int a{3}, b{5};
    std::cout << a << " + " << b << " = " << calc.Sum(a, b) << "\n"
              << a << " * " << b << " = " << calc.Multiply(a, b) << "\n";

    return 0;
}
