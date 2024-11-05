#include <iostream>
#include <type_traits>

template <typename T, typename = void>
struct has_member_type_data : std::false_type
{
};

template <typename T>
struct has_member_type_data<T, std::void_t<typename T::data>> : std::true_type
{
};

struct A
{
    using data = int;
};

struct B
{
};

int main()
{
    std::cout << std::boolalpha;

    std::cout << "Struct A has member type 'data': " << has_member_type_data<A>::value << "\n"
              << "Struct B has member type 'data': " << has_member_type_data<B>::value << "\n";
}