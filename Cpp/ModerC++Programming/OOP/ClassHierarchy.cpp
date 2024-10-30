#include <iostream>

struct A
{
};

struct B : A
{
};

static void funcA(A a)
{
    std::cout << "funcA\n";
}

static void funcRefA(A &a)
{
    std::cout << "funcRefA\n";
}

static void funcB(B b)
{
    std::cout << "funcB\n";
}

static void funcRefB(B &b)
{
    std::cout << "funcRefB\n";
}

int main()
{
    A a{};
    B b{};

    funcA(b);
    funcRefA(b);

    return EXIT_SUCCESS;
}
