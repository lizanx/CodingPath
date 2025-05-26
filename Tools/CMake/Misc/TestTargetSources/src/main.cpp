#include <iostream>
#include "calc.hpp"

int main(int argc, char *argv[])
{
    std::cout << "1 + 2 = " << Add(1, 2) << "\n"
              << "1 - 2 = " << Subtract(1, 2) << "\n";

    return 0;
}
