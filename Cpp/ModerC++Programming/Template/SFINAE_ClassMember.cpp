#include <iostream>
#include <type_traits>

template <typename T, typename = void>
struct has_static_member_x : std::false_type
{
};

template <typename T>
struct has_static_member_x<T, decltype((void)T::x)> : std::true_type
{
};

template <typename T, typename = void>
struct has_instance_member_y : std::false_type
{
};

template <typename T>
struct has_instance_member_y<T, decltype((void)std::declval<T>().y)> : std::true_type
{
};

struct A
{
    static int x;
};
int A::x{};

struct B
{
    int y;
};

int main()
{
    std::cout << std::boolalpha;

    std::cout << "Struct A has static member x: " << has_static_member_x<A>::value << "\n"
              << "Struct B has static member x: " << has_static_member_x<B>::value << "\n";

    std::cout << "Struct A has instance member x: " << has_instance_member_y<A>::value << "\n"
              << "Struct B has instance member x: " << has_instance_member_y<B>::value << "\n";
}
