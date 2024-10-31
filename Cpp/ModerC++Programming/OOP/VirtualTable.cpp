#include <iostream>

class A
{
    virtual void f()
    {
        std::cout << "A::f()\n";
    }

    virtual void g()
    {
        std::cout << "A::g()\n";
    }
};

class B : A
{
    virtual void f() override
    {
        std::cout << "B::f()\n";
    }

    virtual void g() override
    {
        std::cout << "B::g()\n";
    }
};

int main()
{
    std::cout << "Size of A: " << sizeof(A) << "bytes\n"; // 8bytes, vtable pointer
    std::cout << "Size of B: " << sizeof(B) << "bytes\n"; // 8bytes, vtable pointer

    return EXIT_SUCCESS;
}
