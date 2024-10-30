#include <iostream>

class A
{
public:
    int data{};

protected:
    int id{};
};

class B : A // private inheritance by default
{
};

class C : public A
{
};

int main()
{
    B b{};
    C c{};
    // std::cout << b.data << "\n"; // Due to default private inheritance, A.data is inaccessible here.
    std::cout << c.data << "\n";

    return EXIT_SUCCESS;
}
