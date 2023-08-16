#include <iostream>

template <typename Fn, typename In, typename Out>
constexpr Out fold(Fn function, In* input, size_t length, Out initial)
{
    for (size_t index{}; index < length; ++index)
    {
        initial = function(initial, input[index]);
    }
    return initial;
}

int main() {
    int data[]{ 1, 2, 3, 4, 5 };
    size_t data_len = 5;

    auto sum = fold([](auto x, auto y) { return x + y; },
        data, data_len, 0);
    std::cout << "Sum: " << sum << '\n';

    auto product = fold([](auto x, auto y) { return x * y; },
        data, data_len, 1);
    std::cout << "Product: " << product << '\n';
}