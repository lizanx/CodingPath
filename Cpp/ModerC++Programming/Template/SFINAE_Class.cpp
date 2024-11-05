#include <iostream>
#include <type_traits>

template <typename T, typename Enable = void>
struct A;

// Specialization using SFINAE
template <typename T>
struct A<T, std::enable_if_t<std::is_signed_v<T>>>
{
    A(T data) : data{data} {}
    T data;
};
template <typename T>
struct A<T, std::enable_if_t<!std::is_signed_v<T>>>
{
    A(T data) : data{data} {}
    T data;
};

int main()
{
    A<int> a1{-1};
    A<unsigned> a2{1U};

    std::cout << "Signed value: " << a1.data << "\n"
              << "Unsigned value: " << a2.data << "\n";
}
