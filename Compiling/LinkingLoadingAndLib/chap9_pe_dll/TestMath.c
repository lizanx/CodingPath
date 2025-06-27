#include <stdio.h>

__declspec(dllimport) double Sub(double, double);

int main(int argc, char *argv[])
{
    double a = 6, b = 3;

    printf("%lf - %lf = %lf\n", a, b, Sub(a, b));

    return 0;
}
