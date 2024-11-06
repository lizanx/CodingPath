#include <iostream>

template <typename... TArgs>
auto add(TArgs... args)
{
    return (... + args);
}

template <typename T>
T square(T arg)
{
    return arg * arg;
}

template <typename... TArgs>
auto add_square(TArgs... args)
{
    return (square(args) + ...);
}

int main()
{
    std::cout << add(1, 3, 5, 7) << "\n";
    std::cout << add_square(1, 2, 3) << "\n";

    return EXIT_SUCCESS;
}