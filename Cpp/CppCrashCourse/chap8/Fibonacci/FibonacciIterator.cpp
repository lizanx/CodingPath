#include "Fibonacci.h"

bool FibonacciIterator::operator!=(int x) const
{
    return current < x;
}

int FibonacciIterator::operator*() const
{
    return current;
}

FibonacciIterator& FibonacciIterator::operator++()
{
    int tmp{current};
    current += last;
    last = tmp;
    return *this;
}
