#include <iostream>

class Base
{
public:
    virtual void Foo()
    {
        std::cout << "Base::Foo\n";
    }

    virtual void Bar()
    {
        std::cout << "Base::Bar\n";
    }

    virtual void Fn()
    {
        std::cout << "Base::Fn\n";
    }
};

class Derived1 : public virtual Base
{
public:
    void Foo() override
    {
        std::cout << "Derived1::Foo Begin\n";
        Bar();
        Fn();
        std::cout << "Derived1::Foo End\n";
    }
};

class Derived2 : public virtual Base
{
public:
    void Bar() override
    {
        std::cout << "Derived2::Bar\n";
    }

    // This override causes compiling failure due to ambiguous overridden of "Foo"
    // in "MostDerived". To fix it, either only one overriding at this hierarchy
    // level, or add further overriding in "MostDerived" for clarity(Line 66).
#if 0
    void Foo() override
    {
        std::cout << "Derived2::Foo\n";
    }
#endif
};

class MostDerived : public Derived1, public Derived2
{
public:
    MostDerived() : Base{}
    {
    }

    void Fn() override
    {
        std::cout << "MostDerived::Fn\n";
    }

#if 0
    void Foo() override
    {
        std::cout << "MostDerived::Foo\n";
    }
#endif
};

int main(int argc, char *argv[])
{
    MostDerived *pMostDerived = new MostDerived{};
    Derived1 *pDerived1 = static_cast<Derived1 *>(pMostDerived);
    Derived2 *pDerived2 = static_cast<Derived2 *>(pMostDerived);
    Base *pBase = static_cast<Base *>(pMostDerived);

    std::cout << "===== Most Derived =====\n";
    pMostDerived->Foo();
    std::cout << "===== Derived1 =====\n";
    pDerived1->Foo();
    std::cout << "===== Derived2 =====\n";
    pDerived2->Foo();
    std::cout << "===== Base =====\n";
    pBase->Foo();

    delete pMostDerived;

    return EXIT_SUCCESS;
}
