#include <iostream>

class Parent
{
public:
    Parent();
    virtual void Foo();
};

class Child : public Parent
{
public:
    Child();
    void Foo() override;
};

class GrandChild : public Child
{
public:
    GrandChild();
    void Foo() override;
};

int main()
{
    {
        std::cout << "### Test Parent ###\n";
        Parent p{};
        std::cout << "\n";
    }
    {
        std::cout << "### Test Child ###\n";
        Child c{};
        std::cout << "\n";
    }
    {
        std::cout << "### Test GrandChild ###\n";
        GrandChild gc{};
        std::cout << "\n";
    }
}

Parent::Parent()
{
    std::cout << "=== Constructing Parent ===\n";
    Foo();
    std::cout << "=== Parent Constructed ===\n";
}

void Parent::Foo()
{
    std::cout << "Parent::Foo()\n";
}

Child::Child()
{
    std::cout << "=== Constructing Child ===\n";
    Foo();
    std::cout << "=== Child Constructed ===\n";
}

void Child::Foo()
{
    std::cout << "Child::Foo()\n";
}

GrandChild::GrandChild()
{
    std::cout << "=== Constructing GrandChild ===\n";
    Foo();
    std::cout << "=== GrandChild Constructed ===\n";
}

void GrandChild::Foo()
{
    std::cout << "GrandChild::Foo()\n";
}
