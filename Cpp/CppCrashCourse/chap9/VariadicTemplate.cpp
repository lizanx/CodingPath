#include <iostream>

template<typename T>
constexpr T sum(T x)
{
    return x;
}

template<typename T, typename... Args>
constexpr T sum(T x, Args... args)
{
    return x + sum(args...);
}

template<typename... T>
constexpr auto sum_fold(T... args)
{
    return (... + args);
}

int main(void)
{
    std::cout << sum(1, 2, 3, 4, 5) << '\n';
    std::cout << sum_fold(9, 8, 7, 6) << '\n';
    return EXIT_SUCCESS;
}