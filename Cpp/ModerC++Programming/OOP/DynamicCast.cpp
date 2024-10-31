#include <iostream>

class A
{
public:
    int dataA;

    virtual void f()
    {
        std::cout << "A::f()\n";
    }

    virtual ~A() {}
};

class B : public A
{
public:
    int dataB;

    void f() override
    {
        std::cout << "B::f()\n";
    }

    virtual ~B() {}
};

int main()
{
    A a{};
    B b{};

    A &a1 = dynamic_cast<A &>(b); // OK, upcasting
    a1.f();

    A *a2 = dynamic_cast<A *>(&b); // OK, upcasting
    a2->f();

    try
    {
        B &b1 = dynamic_cast<B &>(a); // Fail, throws std::bad_cast
    }
    catch (const std::bad_cast &e)
    {
        std::cerr << "Failed to cast a to B&:\t" << e.what() << '\n';
    }

    B *b2 = dynamic_cast<B *>(&a); // Fail, returns null_ptr
    if (!b2)
        std::cerr << "Failed to cast &a to B*\n";
    else
        std::cout << "Successfully cast &a to B*\n";

    return EXIT_SUCCESS;
}
