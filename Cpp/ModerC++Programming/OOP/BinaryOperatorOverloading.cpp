#include <iostream>

class BaseA
{
public:
    int DataA;

    BaseA() = default;

    BaseA(int data) : DataA{data} {}
};

class DerivedA : public BaseA
{
public:
    DerivedA() = default;

    DerivedA(int data) : BaseA(data) {}

    bool operator==(const BaseA &a)
    {
        return DataA == a.DataA;
    }
};

class BaseB
{
public:
    int DataB;

    BaseB() = default;

    BaseB(int data) : DataB{data} {}
};

class DerivedB : public BaseB
{
public:
    DerivedB() = default;

    DerivedB(int data) : BaseB(data) {}

    friend bool operator==(const BaseB &b1, const BaseB &b2) // Without "friend", compiler error
    {
        return b1.DataB == b2.DataB;
    }
};

int main()
{
    BaseA a{};
    DerivedA A{1};
    BaseB b{2};
    DerivedB B{2};

    // std::cout << (a == A) << "\n"; // Compiler error
    std::cout << (A == a) << "\n";
    std::cout << (b == B) << "\n";
    std::cout << (B == b) << "\n";
}
