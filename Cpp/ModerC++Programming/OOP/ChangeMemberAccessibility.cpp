#include <iostream>

class A
{
public:
    int dataA;
};

class B : A // private inheritance by default
{
public:
    int dataB;
};

class C : public A // explicitly public inheritance
{
public:
    int dataC;
};

class D : A
{
public:
    using A::dataA; // change the member visibility via "using"
};

int main()
{
    A a{};
    std::cout << "A::dataA = " << a.dataA << "\n";

    B b{};
    // std::cout << "B::dataA = " << b.dataA << "\n"; // Cannot access "dataA" due to private inheritance

    C c{};
    std::cout << "C::dataA = " << c.dataA << "\n";

    D d{};
    std::cout << "D::dataA = " << d.dataA << "\n";

    return EXIT_SUCCESS;
}
