#include <iostream>
#include <utility>

template <typename T>
void f(T &var)
{
    std::cout << "f(lvalue ref)\n";
}

template <typename T>
void f(T &&var)
{
    std::cout << "f(rvalue ref)\n";
}

template <typename T>
void g1(T &&var)
{
    std::cout << "g1: without perfect forwarding\n";
    f(var);
}

template <typename T>
void g2(T &&var)
{
    std::cout << "g2: with perfect forwarding\n";
    f(std::forward<T>(var));
}

struct A
{
    int data;
};

int main()
{
    A a{1};
    f(a);
    f(A{2});
    g1(a);
    g1(A{3});
    g2(a);
    g2(A{4});
}