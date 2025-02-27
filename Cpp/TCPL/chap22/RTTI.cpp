#include <iostream>
#include <typeindex>
#include <typeinfo>

class VirtualBase
{
public:
    virtual void Foo() = 0;
    virtual ~VirtualBase() = default;
};

class NonVirtualBase
{
public:
    void Foo();
};

class DerivedA : public VirtualBase
{
public:
    void Foo() override;
};

class DerivedB : public VirtualBase
{
public:
    void Foo() override;
};

class DerivedX : public NonVirtualBase
{
public:
    void Bar();
};

class DerivedY : public NonVirtualBase
{
public:
    void Bar();
};

int main(int argc, char *argv[])
{
    NonVirtualBase base{};
    DerivedA a{};
    DerivedB b{};
    DerivedX x{};
    DerivedY y{};

    std::cout << std::boolalpha;
    {
        // For polymorphic inheritance(with virtual function),
        // "typeid" will always reflect actual runtime type info.
        VirtualBase *p{&a};
        std::cout << typeid(*p).name() << " | "
                  << (typeid(*p) == typeid(DerivedA)) << " | "
                  << std::type_index{typeid(*p)}.name() << "\n";
        p = &b;
        std::cout << typeid(*p).name() << " | "
                  << (typeid(*p) == typeid(DerivedB)) << " | "
                  << std::type_index{typeid(*p)}.name() << "\n";

        std::cout << "\n\n";
    }

    {
        // For non-polymorphic inheritance(without virtual function),
        // "typeid" will only reflect compile-time type info, not runtime info!!
        NonVirtualBase *p{&base};
        std::cout << typeid(*p).name() << " | "
                  << (typeid(*p) == typeid(NonVirtualBase)) << " | "
                  << std::type_index{typeid(*p)}.name() << "\n";
        p = &x;
        std::cout << typeid(*p).name() << " | "
                  << (typeid(*p) == typeid(DerivedX)) << " | "
                  << std::type_index{typeid(*p)}.name() << "\n";
        p = &y;
        std::cout << typeid(*p).name() << " | "
                  << (typeid(*p) == typeid(DerivedY)) << " | "
                  << std::type_index{typeid(*p)}.name() << "\n";
    }
}

void NonVirtualBase::Foo()
{
    std::cout << "NonVirtualBase::Foo\n";
}

void DerivedA::Foo()
{
    std::cout << "DerivedA::Foo\n";
}

void DerivedB::Foo()
{
    std::cout << "DerivedB::Foo\n";
}

void DerivedX::Bar()
{
    std::cout << "DerivedX::Bar\n";
}

void DerivedY::Bar()
{
    std::cout << "DerivedY::Bar\n";
}
