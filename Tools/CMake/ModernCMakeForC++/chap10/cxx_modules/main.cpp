import math;

#include <iostream>

int main()
{
    int a{7}, b{3};

    std::cout << "a + b = " << add(a, b) << "\n"
              << "a - b = " << sub(a, b) << "\n"
              << "a * b = " << multiply(a, b) << "\n"
              << "a / b = " << divide(a, b) << "\n";
}
