#include "calc.hpp"

Calculator::Calculator(IRandomNumberGenerator *randomNumberGenerator)
    : _randomNumberGenerator{randomNumberGenerator}
{
}

int Calculator::Sum(int a, int b)
{
    return a + b;
}

int Calculator::Multiply(int a, int b)
{
    // return a * a; // mistake!!!
    return a * b;
}

int Calculator::AddRandomNumber(int a)
{
    return _randomNumberGenerator->Get() + a;
}
