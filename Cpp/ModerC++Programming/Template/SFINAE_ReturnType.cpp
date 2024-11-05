#include <iostream>
#include <type_traits>

template <typename T>
std::enable_if_t<std::is_signed_v<T>, T> f(T arg)
{
    std::cout << "Signed value: " << arg << "\n";
    return arg;
}

template <typename T>
std::enable_if_t<!std::is_signed_v<T>, T> f(T arg)
{
    std::cout << "Unsigned value: " << arg << "\n";
    return arg;
}

int main()
{
    std::cout << f(-1) << "\n"
              << f(1U) << "\n";
}