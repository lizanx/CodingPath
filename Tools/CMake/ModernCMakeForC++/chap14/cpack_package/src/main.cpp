#include <iostream>
#include "calc.hpp"

int main(int argc, char *argv[])
{
    Calculator calc{};
    std::cout << "2 + 1 = " << calc.Sum(2, 1) << "\n";
    return 0;
}
