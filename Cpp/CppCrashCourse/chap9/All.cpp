#include <iostream>

template <typename Fn, typename In>
constexpr bool all(Fn function, In* input, size_t length)
{
    for (size_t i{}; i < length; ++i)
    {
        if (!function(input[i]))
            return false;
    }
    return true;
}

int main() {
    int data[]{ 100, 200, 300, 400, 500 };
    size_t data_len = 5;

    bool all_gt100 = all([](int x) { return x > 100; }, data, data_len);
    if (all_gt100)
        std::cout << "All elements greater than 100.\n";
    
    bool all_multipleOf100 = all([](int x) { return x % 100 == 0; }, data, data_len);
    if (all_multipleOf100)
        std::cout << "All elements are multiple of 100.\n";
}