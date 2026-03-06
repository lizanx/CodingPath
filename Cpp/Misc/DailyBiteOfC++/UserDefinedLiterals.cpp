#include <cassert>
#include <print>

namespace
{
    namespace units
    {
        struct m
        {
            unsigned long long value;
            friend auto operator<=>(const m &, const m &) = default;
        };

        struct km
        {
            unsigned long long value;
            operator m() const { return {value * 1000}; }
            friend auto operator<=>(const km &, const km &) = default;
        };
    }

    constexpr units::m operator""_m(unsigned long long value)
    {
        return {value};
    }

    constexpr units::km operator""_km(unsigned long long value)
    {
        return {value};
    }
}

int main()
{
    assert(100_m < 1_km);
    assert(1001_m > 1_km);
    assert(1000_m == 1_km);
}
