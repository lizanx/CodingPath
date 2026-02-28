#include <cmath>
#include <compare>
#include <iostream>

namespace
{
    using CompareIntType = decltype(1 <=> 0);
    static_assert(std::is_same_v<CompareIntType, std::strong_ordering>);

    struct Coordinate
    {
        int x;
        int y;
        friend auto operator<=>(const Coordinate &, const Coordinate &) = default;
    };
    using CompareCoordinateType = decltype(Coordinate{0, 0} <=> Coordinate{1, 1});
    static_assert(std::is_same_v<CompareCoordinateType, std::strong_ordering>);

    struct Point : Coordinate
    {
        int GetMagnitude() const
        {
            return x * x + y * y;
        }

        friend std::weak_ordering operator<=>(const Point &left, const Point &right)
        {
            return left.GetMagnitude() <=> right.GetMagnitude();
        }

        friend bool operator==(const Point &, const Point &) = default;
    };
    using ComparePointType = decltype(Point{0, 0} <=> Point{1, 1});
    static_assert(std::is_same_v<ComparePointType, std::weak_ordering>);

    using CompareFloatType = decltype(-0.0 <=> 0.0);
    static_assert(std::is_same_v<CompareFloatType, std::partial_ordering>);

    // Test ordering
    void TestOrdering(const char *name, auto orderingResult)
    {
        std::cout << name << ": \n"
                  << "\t<0 -> " << (orderingResult < 0) << "\n"
                  << "\t==0 -> " << (orderingResult == 0) << "\n"
                  << "\t>0 -> " << (orderingResult > 0) << "\n"
                  << "\tis_lt -> " << (std::is_lt(orderingResult)) << "\n"
                  << "\tis_eq -> " << (std::is_eq(orderingResult)) << "\n"
                  << "\tis_gt -> " << (std::is_gt(orderingResult)) << "\n";

        if constexpr (std::is_same_v<decltype(orderingResult), std::partial_ordering>)
        {
            std::cout << "\tis_unordered -> " << (orderingResult == std::partial_ordering::unordered);
        }
        std::cout << "\n";
    }

    void TestAllOrdering()
    {
        TestOrdering("Strong Less", std::strong_ordering::less);
        TestOrdering("Strong Equal", std::strong_ordering::equivalent);
        TestOrdering("Strong Greater", std::strong_ordering::greater);

        TestOrdering("Weak Less", std::weak_ordering::less);
        TestOrdering("Weak Equal", std::weak_ordering::equivalent);
        TestOrdering("Weak Greater", std::weak_ordering::greater);

        TestOrdering("Partial Less", std::partial_ordering::less);
        TestOrdering("Partial Equal", std::partial_ordering::equivalent);
        TestOrdering("Partial Greater", std::partial_ordering::greater);
        TestOrdering("Partial Unordered", std::partial_ordering::unordered);
    }
}

int main()
{
    bool a = -0.0 == 0.0;
    bool b = std::signbit(-0.0) == std::signbit(0.0);
    bool c = (NAN == 0.0) || (NAN < 0.0) || (NAN > 0.0);
    std::cout << std::boolalpha
              << "-0.0 == 0.0 ? " << a << '\n'
              << "std::signbit(-0.0) == std::signbit(0.0) ? " << b << '\n'
              << "(NAN == 0.0) || (NAN < 0.0) || (NAN > 0.0) ? " << c << '\n';

    std::cout << "\n\n";
    TestAllOrdering();

    return 0;
}
