#include <cassert>
#include <variant>

namespace
{
    struct X
    {
        X(int v) : m_v{v} {}
        int m_v;
    };

    struct Y
    {
        Y(int v) : m_v{v} {}
        int m_v;
    };
}

int main()
{
    // X is non-default-constructible, thus cannot compile.
    // std::variant<X, Y> v1{};
    // Y is non-default-constructible, thus cannot compile.
    // std::variant<Y, X> v2{};

    std::variant<X, Y> v3 = Y{20};
    assert(v3.index() == 1);

    std::variant<std::monostate, X, Y> v4{};
    assert(v4.index() == 0);
    assert(std::holds_alternative<std::monostate>(v4));

    std::variant<int, double> v5{};
    std::variant<int, double> v6{0};
    assert(v5 == v6);

    std::variant<std::monostate, int, double> v7{};
    std::variant<std::monostate, int, double> v8{0};
    assert(v7 != v8);

    return 0;
}
