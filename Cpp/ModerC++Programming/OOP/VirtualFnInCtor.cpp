#include <iostream>

struct A
{
    A()
    {
        std::cout << "---A::A() Start---\n";
        Foo();
        Bar();
        std::cout << "---A::A() End---\n";
    }

    virtual ~A()
    {
        std::cout << "---A::~A() Start---\n";
        Foo();
        Bar();
        std::cout << "---A::~A() End---\n";
    }

    virtual void Foo()
    {
        std::cout << "A::Foo()\n";
    }

    virtual void Bar()
    {
        std::cout << "A::Bar()\n";
    }
};

struct B : A
{
    B()
    {
        std::cout << "---B:B() Start---\n";
        Foo();
        Bar();
        std::cout << "---B:B() End---\n";
    }

    virtual ~B()
    {
        std::cout << "---B::~B() Start---\n";
        Foo();
        Bar();
        std::cout << "---B::~B() End---\n";
    }

    void Foo() override
    {
        std::cout << "B:Foo()\n";
    }
};

struct C : B
{
    C()
    {
        std::cout << "---C:C() Start---\n";
        Foo();
        Bar();
        std::cout << "---C:C() End---\n";
    }

    virtual ~C()
    {
        std::cout << "---C::~C() Start---\n";
        Foo();
        Bar();
        std::cout << "---C::~C() End---\n";
    }

    void Foo() override
    {
        std::cout << "C:Foo()\n";
    }

    void Bar() override
    {
        std::cout << "C::Bar()\n";
    }
};

int main()
{
    {
        B b{};
    }

    std::cout << "\n--------------------------------------------------\n";

    {
        C c{};
    }

    return EXIT_SUCCESS;
}
