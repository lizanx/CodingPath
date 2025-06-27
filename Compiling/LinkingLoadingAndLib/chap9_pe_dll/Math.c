#if 0

__declspec(dllexport) double Add(double a, double b)
{
    return a + b;
}

__declspec(dllexport) double Sub(double a, double b)
{
    return a - b;
}

__declspec(dllexport) double Mul(double a, double b)
{
    return a * b;
}

#else

double Add(double a, double b)
{
    return a + b;
}

double Sub(double a, double b)
{
    return a - b;
}

double Mul(double a, double b)
{
    return a * b;
}

#endif
