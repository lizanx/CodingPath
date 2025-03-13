#include <iostream>
#include <string>
#include <tuple>

namespace
{

}

int main()
{
    using namespace std::string_literals;
    auto t1 = std::make_tuple(1, "One"s, 2.2);
    auto t2 = std::make_tuple(-10, "Negative Ten"s, 9.9);
    std::cout << "Number of elements in t1: "
              << std::tuple_size_v<decltype(t1)> << '\n';
    std::cout << "Number of elements in t2: "
              << std::tuple_size_v<decltype(t2)> << '\n';

    auto i = std::get<0>(t1);
    std::cout << "t1<0> = " << i << '\n';
    i = std::get<int>(t1);
    std::cout << "t1<int> = " << i << '\n';

    typename std::tuple_element_t<2, decltype(t1)> d = 3.3;
    typename std::tuple_element_t<1, decltype(t2)> str = "Hello";

    std::tie(i, str, d) = t1;
    std::cout << "After tie and assignment, i = " << i
              << ", str = " << str
              << ", d = " << d
              << '\n';

    // auto [i, str, d] = t2; // error: redefinition
    auto [i2, str2, d2] = t2;
    std::cout << "After structured-binding, i2 = " << i2
              << ", str2 = " << str2
              << ", d2 = " << d2
              << '\n';
}
