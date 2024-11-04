#include <iostream>

template <typename T>
struct A
{
    T data;
};

template <typename T>
struct B
{
    T data;
};

template <typename T1, typename T2>
struct C
{
    T1 data1;
    T2 data2;
};

template <typename T>
void f()
{
    std::cout << "f<" << typeid(T).name() << ">()\n";
}

template <typename T>
void g()
{
    std::cout << "g<" << typeid(T).name() << ">()\n";
}

class Tmp
{
    friend void f<int>(); // OK, template function instantiation

    template <typename T>
    friend void g(); // OK, all template functions

    friend struct A<int>; // OK, template class instantiation

    template <typename T>
    friend struct B; // OK, all template classes

    template <typename T1, typename T2>
    friend class C; // OK, all template classes

    // template <typename T>
    // friend class C<int, T>; // Error: partial specialization cannot be declared as a friend
};

int main()
{
    Tmp tmp{};
}
