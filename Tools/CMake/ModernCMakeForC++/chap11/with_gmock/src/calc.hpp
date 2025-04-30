#pragma once
#include "rng.hpp"

class Calculator
{
private:
    IRandomNumberGenerator* _randomNumberGenerator;

public:
    Calculator(IRandomNumberGenerator* randomNumberGenerator);
    int Sum(int a, int b);
    int Multiply(int a, int b);
    int AddRandomNumber(int a);
};
