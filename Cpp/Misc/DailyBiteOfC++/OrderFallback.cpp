#include <cassert>
#include <compare>

namespace
{
    struct Coordinate
    {
        int x;
        int y;
        friend bool operator<(const Coordinate &left, const Coordinate &right);
        friend bool operator==(const Coordinate &left, const Coordinate &right);
    };

    bool operator<(const Coordinate &left, const Coordinate &right)
    {
        return (left.x != right.x) ? (left.x < right.x) : (left.y < right.y);
    }

    bool operator==(const Coordinate &left, const Coordinate &right)
    {
        return left.x == right.x && left.y == right.y;
    }
}

int main()
{
    Coordinate a{1, 2}, b{2, 2};

    auto s = std::compare_strong_order_fallback(a, b);
    static_assert(std::is_same_v<decltype(s), std::strong_ordering>);
    assert(std::is_lt(s));

    auto w = std::compare_weak_order_fallback(a, b);
    static_assert(std::is_same_v<decltype(w), std::weak_ordering>);
    assert(std::is_lt(w));

    auto p = std::compare_partial_order_fallback(a, b);
    static_assert(std::is_same_v<decltype(p), std::partial_ordering>);
    assert(std::is_lt(p));

    return 0;
}
