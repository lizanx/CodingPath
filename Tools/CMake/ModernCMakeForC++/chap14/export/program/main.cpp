#include <iostream>
#include "calc.hpp"

int main()
{
    Calculator calc{};
    std::cout << "3 * 4 = " << calc.Multiply(3, 4) << "\n";
    return 0;
}
