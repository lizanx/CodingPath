#include <iostream>

namespace
{
struct Foo
{
    int a;
    int b;
    int c;
    int d;
};
} // namespace

int main()
{
    int Foo::*p{};
    Foo foo{1, 2, 3, 4};
    Foo *pFoo{&foo};

    p = nullptr;
    std::cout << "(p) = " << p << "\n";
    std::cout << "*(int*)&p = " << *(int *)&p << "\n";

    p = &Foo::a;
    std::cout << "(p) = " << p << "\n";
    std::cout << "*(int*)&p = " << *(int *)&p << "\n";
    std::cout << "foo.*p = " << foo.*p << "\n";
    std::cout << "pFoo->*p = " << pFoo->*p << "\n";
    p = &Foo::b;
    std::cout << "(p) = " << p << "\n";
    std::cout << "*(int*)&p = " << *(int *)&p << "\n";
    std::cout << "foo.*p = " << foo.*p << "\n";
    std::cout << "pFoo->*p = " << pFoo->*p << "\n";
    p = &Foo::c;
    std::cout << "(p) = " << p << "\n";
    std::cout << "*(int*)&p = " << *(int *)&p << "\n";
    std::cout << "foo.*p = " << foo.*p << "\n";
    std::cout << "pFoo->*p = " << pFoo->*p << "\n";
    p = &Foo::d;
    std::cout << "(p) = " << p << "\n";
    std::cout << "*(int*)&p = " << *(int *)&p << "\n";
    std::cout << "foo.*p = " << foo.*p << "\n";
    std::cout << "pFoo->*p = " << pFoo->*p << "\n";
}
