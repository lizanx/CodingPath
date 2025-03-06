#include <iostream>

class Base
{
public:
    virtual ~Base();
    virtual void Foo();
};

class Derived : public Base
{
public:
    ~Derived() override;
    void Foo() override;
};

int main()
{
    {
        Derived d{};
        Base &b{d};
        b.Foo();
    }
    std::cout << "============================\n";
    {
        Derived d{};
        d.Foo();
    }
}

Base::~Base()
{
    std::cout << "Base::~Base()\n";
}

void Base::Foo()
{
    std::cout << "Base::Foo()\n";
}

Derived::~Derived()
{
    std::cout << "Derived::~Derived()\n";
}

void Derived::Foo()
{
    std::cout << "Derived::Foo()\n";
}
