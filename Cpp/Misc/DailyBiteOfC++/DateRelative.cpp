#include <cassert>
#include <chrono>
#include <print>

int main()
{
    namespace sc = std::chrono;
    using namespace std::chrono_literals;

    // Last day in a month
    {
        auto lastDayInFeb = sc::February / sc::last;
        static_assert(std::is_same_v<decltype(lastDayInFeb), sc::month_day_last>);
        std::println("Last day in Feb: {}", lastDayInFeb);
        sc::year_month_day actual{2026y / lastDayInFeb};
        std::println("Last day in Feb[actual]: {}", actual);
    }
    std::println("\n");

    // Find leap years
    for (auto year = 2026y; year < 2050y; ++year)
    {
        auto lastDayInFeb = year / sc::February / sc::last;
        assert(lastDayInFeb.ok());
        if (lastDayInFeb.day() == 29d)
        {
            std::println("Leap year: {}", year);
        }
    }
    std::println("\n");

    // Last weekday in a month
    auto lastSundayInDecember = sc::December / sc::Sunday[sc::last];
    static_assert(std::is_same_v<decltype(lastSundayInDecember), sc::month_weekday_last>);
    for (auto year = 2026y; year <= 2030y; ++year)
    {
        auto lastSundayInYear = year / lastSundayInDecember;
        sc::year_month_day actual{lastSundayInYear};
        std::println("Last Sunday of {}: {}", actual.year(), actual);
    }
    std::println("\n");

    // n-th weekday in a month
    auto thanksGiving = sc::November / sc::Thursday[4];
    static_assert(std::is_same_v<decltype(thanksGiving), sc::month_weekday>);
    for (auto year = 2026y; year < 2030y; ++year)
    {
        sc::year_month_day actual{year / thanksGiving};
        std::println("Thanks Giving day of {}: {}", actual.year(), actual);
    }

    return 0;
}