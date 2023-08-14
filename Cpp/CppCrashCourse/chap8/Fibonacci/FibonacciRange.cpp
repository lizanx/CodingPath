#include <stdexcept>
#include "Fibonacci.h"

FibonacciRange::FibonacciRange(int max): max{max}
{
    if (max <= 1) throw std::invalid_argument("Invalid max value.");
}

FibonacciIterator FibonacciRange::begin() const
{
    return FibonacciIterator{};
}

int FibonacciRange::end() const
{
    return max;
}
