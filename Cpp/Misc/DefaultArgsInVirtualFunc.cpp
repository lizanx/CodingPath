#include <iostream>

// Don't use default arguments in virtual functions.
// Because virtual functions are dynamically bound at runtime,
// while default arguments are determined by static type at compile time.

namespace
{
class Base
{
  public:
    virtual void Print(int x = 10)
    {
        std::cout << "[Base] x = " << x << "\n";
    }
};

class Derived : public Base
{
  public:
    void Print(int x = 20) override
    {
        std::cout << "[Derived] x = " << x << "\n";
    }
};
} // namespace

int main()
{
    Base base{};
    base.Print();
    Derived derived{};
    derived.Print();

    std::cout << "============\n";
    Base *ptr = &base;
    ptr->Print();
    ptr = &derived;
    ptr->Print();

    std::cout << "============\n";
    Base &ref1 = base;
    ref1.Print();
    Base &ref2 = derived;
    ref2.Print();
}
