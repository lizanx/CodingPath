#include <iostream>

struct A
{
    void f() &
    {
        std::cout << "f() &" << "\n";
    }

    void f() &&
    {
        std::cout << "f() &&" << "\n";
    }
};

int main()
{
    A a{};
    a.f();
    A{}.f();
    std::move(a).f();
}
