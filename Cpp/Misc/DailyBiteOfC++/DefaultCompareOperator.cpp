#include <cassert>
#include <compare>
#include <string>

namespace
{
    class Base
    {
    public:
        Base(int data) : m_data{data} {}
        friend auto operator<=>(const Base &, const Base &) = default;

    private:
        int m_data{};
    };

    class Derived : public Base
    {
    public:
        Derived(int d1, int d2) : Base{d1}, m_derivedData{d2} {}
        friend auto operator<=>(const Derived &, const Derived &) = default;

    private:
        int m_derivedData{};
    };

    class Point
    {
    public:
        Point(double x, double y) : m_x{x}, m_y{y} {}
        friend bool operator==(const Point &, const Point &) = default;

    private:
        double m_x{};
        double m_y{};
    };
}

int main()
{
    Base b1{1}, b2{2};
    Derived d1{3, 4}, d2{5, 6};
    assert(b1 != b2);
    assert(std::is_neq(b1 <=> b2));
    assert(d1 != d2);
    assert(std::is_neq(d1 <=> d2));
    assert(b1 != d1);
    assert(std::is_neq(b2 <=> d2));

    Point p1{1.0, 2.0}, p2{1.0, 2.0};
    assert(p1 == p2);

    return 0;
}
