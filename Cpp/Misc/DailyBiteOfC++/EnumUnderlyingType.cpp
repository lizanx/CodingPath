#include <cstdint>
#include <print>
#include <type_traits>
#include <utility>

namespace
{
    enum Color
    {
        Red,
        Green,
        Blue
    };

    enum Info : unsigned long long
    {
        Limit = UINT64_MAX
    };

    enum class Vehicle
    {
        Car,
        Plane,
        Motor,
        Bike,
        Ship
    };
}

int main()
{
    // C++11
    auto a = static_cast<std::underlying_type<Color>::type>(Color::Red);
    static_assert(std::is_same_v<decltype(a), unsigned int>);
    // C++14
    auto b = static_cast<std::underlying_type_t<Info>>(Info::Limit);
    static_assert(std::is_same_v<decltype(b), unsigned long long>);
    // C++23
    auto c = std::to_underlying(Vehicle::Ship);
    static_assert(std::is_same_v<decltype(c), int>);

    std::println("a = {}, b = {}, c = {}", a, b, c);

    return 0;
}
