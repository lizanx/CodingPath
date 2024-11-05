#include <iostream>
#include <type_traits>

template <typename T, std::enable_if_t<std::is_signed_v<T>, int> = 0>
void f(T arg)
{
    std::cout << "Signed value: " << arg << "\n";
}

template <typename T, std::enable_if_t<!std::is_signed_v<T>, int> = 0>
void f(T arg)
{
    std::cout << "Unsigned value: " << arg << "\n";
}

int main()
{
    f(-1);
    f(1U);
}
