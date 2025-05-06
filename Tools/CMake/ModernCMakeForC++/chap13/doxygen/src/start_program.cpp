#include "calc.hpp"
#include <iostream>

int StartProgram(int argc, const char *argv[])
{
    auto pCalc = new Calculator();
    int a{3}, b{5};
    std::cout << a << " + " << b << " = " << pCalc->Sum(a, b) << "\n"
              << a << " * " << b << " = " << pCalc->Multiply(a, b) << "\n";

    delete pCalc;
    return 0;
}
