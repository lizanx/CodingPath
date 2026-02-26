#include <print>

namespace
{
    // default ctor
    struct A
    {
        int data;
    };

    // default ctor
    struct B
    {
        B() = default;

        int data;
    };

    // user-defined ctor
    struct C
    {
        constexpr C() {}

        int data;
    };
}

int main()
{
    A a1, a2{};
    std::println("a1: {}, a2: {}", a1.data, a2.data);
    B b1, b2{};
    std::println("b1: {}, b2: {}", b1.data, b2.data);
    C c1, c2{};
    std::println("c1: {}, c2: {}", c1.data, c2.data);
    // a1: 4607, a2: 0
    // b1: 29244, b2: 0
    // c1: 0, c2: 1
    /* 'data' of 'a1/b1/c1' is not initialized!
     * 'data` of `a2/b2' is initialized to 0, while 'c2.data' is not initialized since 'class C' has user-defined ctor!
     */

    constexpr A a{}; // OK
    constexpr B b{}; // OK
    // constexpr C c{}; // error: access to uninitialized subobject (member "<unnamed>::C::data")

    return 0;
}
