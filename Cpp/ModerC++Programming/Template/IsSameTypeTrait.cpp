#include <iostream>
#include <type_traits>

// By default, any two types are not the same
template <typename T1, typename T2>
struct is_same : std::false_type
{
};

// Use template specialization for only one type
template <typename T>
struct is_same<T, T> : std::true_type
{
};

int main()
{
    std::cout << std::boolalpha << is_same<int, char>::value << "\n";
    std::cout << std::boolalpha << is_same<int, int>::value << "\n";
    std::cout << std::boolalpha << is_same<int, int *>::value << "\n";
    std::cout << std::boolalpha << is_same<long, long>::value << "\n";
}
