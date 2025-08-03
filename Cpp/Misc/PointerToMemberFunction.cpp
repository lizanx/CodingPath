#include <iostream>

namespace
{
class Base
{
  public:
    Base()
    {
    }

    void NonVirtualFunc()
    {
        std::cout << "Base::NonVirtualFunc()\n";
    }

    virtual void VirtualFunc()
    {
        std::cout << "Base::VirtualFunc()\n";
    }
};

class Derived : public Base
{
  public:
    Derived() : Base()
    {
    }

    void NonVirtualFunc()
    {
        std::cout << "Derived::VirtualFunc()\n";
    }

    void VirtualFunc() override
    {
        std::cout << "Derived::VirtualFunc()\n";
    }
};
} // namespace

int main()
{
    void (Base::*pNonVirtualFunc)() = &Base::NonVirtualFunc;
    void (Base::*pVirtualFunc)() = &Base::VirtualFunc;

    std::cout << "============= Base =============\n";
    Base b{};
    (b.*pNonVirtualFunc)();
    (b.*pVirtualFunc)();
    Base *pb{&b};
    (pb->*pNonVirtualFunc)();
    (pb->*pVirtualFunc)();

    std::cout << "============= Derived =============\n";
    Derived d{};
    (d.*pNonVirtualFunc)();
    (d.*pVirtualFunc)(); // will call Derived::Virtual
    pb = &d;
    (pb->*pNonVirtualFunc)();
    (pb->*pVirtualFunc)(); // will call Derived::Virtual
}
