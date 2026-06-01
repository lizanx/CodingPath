#include <stdio.h>

// OK(default int argument), but not recommended
static void f1();
static void g1()
{
    printf("g1\n");
    f1(1);
}
static void f1(int n)
{
    printf("f1: n -> %d\n", n);
}

// OK(default double argument), not not recommended
static void f2();
static void g2()
{
    printf("g2\n");
    f2(2.0);
}
static void f2(double d)
{
    printf("f2: d -> %lf\n", d);
}

// Error, 'float' is not default promotion arg type
// static void f3();
// static void g3()
// {
//     printf("g3\n");
//     f3(3.0);
// }
// static void f3(float f)
// {
//     printf("f3: f -> %f\n", f);
// }

// OK, recommended modern way
static void f4(float f);
static void g4()
{
    printf("g4\n");
    f4(4.0);
}
static void f4(float f)
{
    printf("f4: f -> %f\n", f);
}

int main()
{
    g1();
    g2();
    // g3();
    g4();

    return 0;
}
