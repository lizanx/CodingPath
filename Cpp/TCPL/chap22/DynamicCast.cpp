#include <iostream>
#include <string>

class VirtualBase
{
public:
    virtual std::string Greeting() const = 0;
};

class NonVirtualBase
{
public:
    std::string Name() const;
};

class Derived : public NonVirtualBase, public VirtualBase
{
public:
    explicit Derived(std::string name);
    std::string Greeting() const override;

private:
    std::string _name;
};

int main(int argc, char *argv[])
{
    auto pDerived = new Derived{"Derived-Class"};

    {
        std::cout << "=== Cast From Virtual Base ===\n";
        VirtualBase *pVirtual = pDerived;
        // Cast from base to derived
        Derived *pTmpDerived = dynamic_cast<Derived *>(pVirtual);
        if (pTmpDerived)
            std::cout << "Successfully cast from virtual base to derived: " << pTmpDerived->Greeting() << "\n";
        else
            std::cout << "Failed to cast from virtual base to derived\n";
        // Cross-cast to non-polymorphic target type:
        // since real type is "Derived" and all its base classes type info is saved,
        // this cast from "Derived" to its base "NonVirtualBase" will work.
        NonVirtualBase *pTmpNonVirtual = dynamic_cast<NonVirtualBase *>(pVirtual);
        if (pTmpNonVirtual)
            std::cout << "Successfully cross-cast from virtual base to non-virtual base: " << pTmpNonVirtual->Name() << "\n";
        else
            std::cout << "Failed to cast from virtual base to non-virtual base\n";

        std::cout << "=== Check Base/Derived Address ===\n"; // Below two addresses may differ from each other.
        std::cout << std::hex;
        std::cout << "Address of VirtualBase: " << dynamic_cast<void *>(pVirtual) << "\n";
        std::cout << "Address of Derived: " << dynamic_cast<void *>(pDerived) << "\n";
    }

    {
        std::cout << "=== Cast From Non-Virtual Base ===\n";
        NonVirtualBase *pNonVirtual = pDerived;
        // Cannot cast from base class with no virtual methods
        Derived *pTmpDerived{};
        // pTmpDerived = dynamic_cast<Derived *>(pNonVirtual); // doesn't compile
        pTmpDerived = static_cast<Derived *>(pNonVirtual); // You know the compile-time type, your own reponsibility for correctness
        std::cout << "static_cast from non-virtual base to derived: " << pTmpDerived->Greeting() << "\n";
        // VirtualBase *pTmpVirtual = static_cast<VirtualBase *>(pNonVirtual); // doesn't compile
    }

    delete pDerived;
    return EXIT_SUCCESS;
}

std::string NonVirtualBase::Name() const
{
    return "NonVirtualBase";
}

Derived::Derived(std::string name) : _name{name}
{
}

std::string Derived::Greeting() const
{
    using namespace std::string_literals;
    return "Greeting from "s + _name;
}
