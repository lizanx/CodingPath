#include <iostream>

template <typename T>
struct Base
{
    T BaseData;

    Base(T data) : BaseData{data} {}

    virtual void PrintBaseData()
    {
        std::cout << "BaseData of class Base: " << BaseData << "\n";
    }
};

template <typename T>
struct Derived : Base<T>
{
    using Base<T>::BaseData; // This line is needed to use "BaseData" in derived class

    T DerivedData;

    Derived(T data) : Base<T>{data}
    {
        DerivedData = data * 2;
    }

    void PrintBaseData() override
    {
        std::cout << "BaseData of class Derived: " << BaseData << "\n";
    }

    void PrintDerivedData()
    {
        std::cout << "DerivedData of class Derived: " << DerivedData << "\n";
    }
};

int main()
{
    Base<int> b{1};
    b.PrintBaseData();

    Derived<int> d{1};
    d.PrintBaseData();
    d.PrintDerivedData();
}
