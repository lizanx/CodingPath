#include <iostream>
#include "calc.hpp"

int main(int argc, char *argv[])
{
    Calculator calc{};
    std::cout << "2 * 3 = " << calc.Multiply(2, 3) << "\n";
    return 0;
}
