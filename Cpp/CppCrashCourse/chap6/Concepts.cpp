#include <iostream>
#include <type_traits>

constexpr const char* as_str(bool x) { return x ? "True" : "False"; }

template<typename T>
concept integral_number = std::is_integral_v<T>;

template<typename T>
concept decimal_number = std::is_floating_point_v<T>;

bool is_same(const integral_number auto& n1, const integral_number auto& n2)
{
    return n1 == n2;
}
bool is_same(const decimal_number auto& d1, const decimal_number auto& d2)
{
    return std::abs(d1 - d2) < decltype(d1){ 0.0001 };
}

template<integral_number T>
bool is_same_sec(const T& n1, const T& n2)
{
    return n1 == n2;
}
template<decimal_number T>
bool is_same_sec(const T& n1, const T& n2)
{
    return std::abs(n1 - n2) < T{ 0.0001 };
}

template<typename T>
    requires integral_number<T>
bool is_same_third(const T& n1, const T& n2)
{
    return n1 == n2;
}
template<typename T>
    requires decimal_number<T>
bool is_same_third(const T& n1, const T& n2)
{
    return std::abs(n1 - n2) < T{ 0.0001 };
}

int main()
{
    std::cout << as_str(std::is_integral<int>::value) << '\n';
    std::cout << as_str(std::is_integral<long>::value) << '\n';
    std::cout << as_str(std::is_integral<char>::value) << '\n';
    std::cout << as_str(std::is_integral<const int>::value) << '\n';
    std::cout << as_str(std::is_integral<int&>::value) << '\n';
    std::cout << as_str(std::is_integral<int*>::value) << '\n';
    std::cout << as_str(std::is_integral<float>::value) << '\n';

    std::cout << is_same(5, 5) << '\t' << is_same(5, 6) << '\n';
    std::cout << is_same(5.5, 5.6) << '\t' << is_same(5.5, 5.50001) << '\n';
    std::cout << std::endl;
    std::cout << is_same_sec(5, 5) << '\t' << is_same_sec(5, 6) << '\n';
    std::cout << is_same_sec(5.5, 5.6) << '\t' << is_same_sec(5.5, 5.50001) << '\n';
    std::cout << std::endl;
    std::cout << is_same_third(5, 5) << '\t' << is_same_third(5, 6) << '\n';
    std::cout << is_same_third(5.5, 5.6) << '\t' << is_same_third(5.5, 5.50001) << '\n';
    std::cout << std::endl;
}