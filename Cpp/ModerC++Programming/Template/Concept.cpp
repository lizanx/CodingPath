#include <iostream>
#include <type_traits>

template <typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

template <typename T>
concept Addable = requires(T a, T b) {
    a + b;
};

template <typename T>
    requires Arithmetic<T>
T add1(T a, T b)
{
    return a + b;
}

template <typename T>
T add2(T a, T b)
    requires Addable<T>
{
    return a + b;
}

template <Addable T>
T add3(T a, T b)
{
    return a + b;
}

template <typename T>
    requires requires(T x, T y) { x + y; }
T add4(T a, T b)
{
    return a + b;
}

int main()
{
    std::cout << add1(1, 2) << "\n"
              << add2(3, 4) << "\n"
              << add3(5, 6) << "\n"
              << add4(7, 8) << "\n";
}