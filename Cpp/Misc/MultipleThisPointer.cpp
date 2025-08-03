#include <iostream>

namespace
{
using std::cout;
struct A
{
    int a{};
    A()
    {
        cout << "A::A() this = " << this << "\n";
    }
    virtual ~A()
    {
        cout << "A::~A() this = " << this << "\n";
    }
    virtual void Bar()
    {
        cout << "A::Bar() this = " << this << "\n";
    }
};
struct B
{
    int b{};
    B()
    {
        cout << "B::B() this = " << this << "\n";
    }
    virtual ~B()
    {
        cout << "B::~B() this = " << this << "\n";
    }
    void Foo()
    {
        cout << "B::Foo() this = " << this << "\n";
    }
};
struct C : public A, public B
{
    int c{};
    C()
    {
        cout << "C::C() this = " << this << "\n";
    }
    virtual ~C()
    {
        cout << "C::~C() this = " << this << "\n";
    }
    void Bar() override
    {
        cout << "C::Bar() this = " << this << "\n";
        Foo();
    }
};

} // namespace

int main(int argc, char *argv[])
{
    using std::cout;
    cout << std::hex;

    cout << "\nC* pC = new C{};\n";
    C *pC = new C{};
    A *pA = pC;
    cout << "\npA = " << pA << " pA->Bar();\n";
    pA->Bar();
    cout << "\npC = " << pC << " pC->Foo();\n";
    pC->Foo();
    B *pB = pC;
    cout << "\npB = " << pB << " delete pB;\n";
    delete pB;
}
