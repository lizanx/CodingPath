#include <iostream>

template <typename T1, typename T2>
auto add(T1 leftOperand, T2 rightOperand)
{
    return leftOperand + rightOperand;
}

template <typename T, typename... TArgs>
auto add(T operand, TArgs... operands)
{
    return operand + add(operands...);
}

template <typename T>
T square(T arg)
{
    return arg * arg;
}

template <typename... TArgs>
auto add_square(TArgs... args)
{
    return add(square(args)...);
}

int main()
{
    std::cout << add_square(1, 2.2, 3, 5.0, 6) << "\n";

    return EXIT_SUCCESS;
}