#include <iostream>
#include <string>
#include <tuple>

int main()
{
    std::tuple<int, double, std::string> t1{1, 1.1, "One/One dot One"};
    std::tuple<int, double, std::string> t2 = {2, 2.2, "Two/Two dot two"};
    auto t3 = std::make_tuple(3, 3.3, std::string{"Three/Three dot three"});

    auto t4 = std::tuple_cat(t1, t2);
    std::cout << "t1 + t2 -> "
              << std::get<0>(t4) << " ,"
              << std::get<1>(t4) << " ,"
              << std::get<2>(t4) << " ,"
              << std::get<3>(t4) << " ,"
              << std::get<4>(t4) << " ,"
              << std::get<5>(t4)
              << "\n";

    std::cout << "Size: t1 -> " << std::tuple_size<decltype(t1)>::value << ", "
              << "t2 -> " << std::tuple_size<decltype(t2)>::value << ", "
              << "t4 -> " << std::tuple_size<decltype(t4)>::value << "\n";

    using MyInt = std::tuple_element<0, decltype(t4)>::type;
    MyInt i = 1;

    int firstElement{};
    double secondElement{};
    std::tie(firstElement, secondElement, std::ignore) = t1;
    std::cout << "Deconstruct t1: first element = " << firstElement
              << ", second element = " << secondElement << "\n";

    auto [a, b, c] = t2;
    std::cout << "Structured binding for t2: "
              << "first element = " << a << ", "
              << "second element = " << b << ", "
              << "third element = " << c << "\n";
}
