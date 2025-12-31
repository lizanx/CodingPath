#include <iostream>

namespace
{
    class Base
    {
    public:
        virtual void Foo() const
        {
            std::cout << "Base::Foo\n";
        }

        virtual void Bar() const
        {
            std::cout << "Base::Bar\n";
        }

        int GetX() const
        {
            return _x;
        }

    private:
        int _x{1};
    };

    class Derived : public Base
    {
    public:
        void Foo() const override
        {
            std::cout << "Derived::Foo\n";
        }

        int GetY() const
        {
            return _y;
        }

    private:
        int _y{2};
    };

    class AnotherBase
    {
    public:
        virtual void Woo() const
        {
            std::cout << "AnotherBase::Woo\n";
        }

        int GetZ() const
        {
            return _z;
        }

    private:
        int _z{3};
    };

    class AnotherDerived : public Base, public AnotherBase
    {
    public:
        void Foo() const override
        {
            std::cout << "AnotherDerived::Foo\n";
        }

        void Woo() const override
        {
            std::cout << "AnotherDerived::Woo\n";
        }

    private:
        int _a{4};
    };
}

int main(int argc, char *argv[])
{
    Base b{};
    std::cout << "Size of b: " << sizeof(b) << "\n"; // vptr + int + padding
    std::cout << "Vtable at " << *((void **)&b) << "\n";

    void **vtable = *((void ***)&b);
    std::cout << "Vtable at " << vtable << "\n";
    using Func = void (*)(Base *);
    std::cout << "Slot[0]: " << (Func)(vtable[0]) << "\n";
    std::cout << "Slot[1]: " << (Func)(vtable[1]) << "\n";
    std::cout << "Calling Foo..\n";
    ((Func)(vtable[0]))(&b);
    std::cout << "Calling Bar..\n";
    ((Func)(vtable[1]))(&b);

    std::cout << "\n=============================\n\n";

    Derived d{};
    std::cout << "Size of d: " << sizeof(d) << "\n"; // vptr + int + int
    void **vtableDerived = *((void ***)&d);
    std::cout << "Vtable for Derived at " << vtableDerived << "\n";
    using FuncDerived = void (*)(Derived *);
    std::cout << "Calling Foo..\n";
    ((FuncDerived)(vtableDerived[0]))(&d);
    std::cout << "Calling Bar..\n";
    ((Func)(vtableDerived[1]))(&d);

    std::cout << "\n=============================\n\n";

    AnotherDerived ad{};
    std::cout << "Size of ad: " << sizeof(ad) << "\n";
    std::cout << "Address of ad: " << &ad << "\n";
    Base *pb = &ad;
    std::cout << "Address of Base: " << pb << "\n";
    AnotherBase *pab = &ad;
    std::cout << "Address of AnotherBase: " << pab << "\n";

    return 0;
}
