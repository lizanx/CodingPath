#include <iostream>
#include "Fibonacci.h"

int main(void)
{
    for (const auto& n : FibonacciRange{5000})
    {
        std::cout << n << ' ';
    }
    std::cout << '\n';
}