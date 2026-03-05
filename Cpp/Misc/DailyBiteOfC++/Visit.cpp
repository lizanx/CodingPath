#include <print>
#include <string>
#include <variant>

namespace
{
    template <typename... Ts>
    struct Overloaded : Ts...
    {
        using Ts::operator()...;
    };
}

int main()
{
    std::variant<int, double, std::string> v{"Hello world"};
    std::visit([](auto &&x)
               { std::println("{}", x); }, v);

    std::println("\n");

    auto visitor = Overloaded{[](int &x)
                              {
                                  std::println("Contains int, value: {}", x);
                              },
                              [](double &x)
                              {
                                  std::println("Contains double, value: {}", x);
                              },
                              [](std::string &x)
                              {
                                  std::println("Contains string, value: {}", x);
                              }};
    std::visit(visitor, v);
    v = 1;
    std::visit(visitor, v);
    v = 2.2;
    std::visit(visitor, v);

    std::println("\n");

    std::variant<std::string, int> a{"Hello"};
    std::variant<double, char> b{'X'};
    std::visit([](auto &&x, auto &&y)
               {
        std::println("First argument:");
        std::println("\ttype -> {}", typeid(x).name());
        std::println("\tvalue -> {}", x);

        std::println("Second argument:");
        std::println("\ttype -> {}", typeid(y).name());
        std::println("\tvalue -> {}", y); },
               a, b);

    std::println("\n");

    std::variant<int, long, float, double> c{3.3};
    // auto r1 = std::visit([](auto e)
    //                      { return e; }, c); // cannot compile
    // Return type must be the same
    auto r2 = std::visit([](auto e)
                         { return static_cast<int>(e); }, c);
    std::println("r2 = {}", r2);
    // C++20: specify return type
    auto r3 = std::visit<int>([](auto e)
                              { return e; }, c);
    std::println("r3 = {}", r3);

    return 0;
}
