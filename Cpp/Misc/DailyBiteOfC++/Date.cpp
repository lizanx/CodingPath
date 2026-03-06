#include <cassert>
#include <chrono>
#include <print>

int main()
{
    namespace sc = std::chrono;
    using namespace std::chrono_literals;

    auto moonDay = 2024y / sc::July / 20d;
    static_assert(std::is_same_v<decltype(moonDay), sc::year_month_day>);

    auto weirdDay = 2024y / sc::June / 44d;
    static_assert(std::is_same_v<decltype(weirdDay), sc::year_month_day>);
    assert(!weirdDay.ok());

    auto sysDate = sc::sys_days{weirdDay}; // 2024/7/14
    auto convertedBackWeirdDay = sc::year_month_day{sysDate};
    assert(static_cast<int>(convertedBackWeirdDay.year()) == 2024);
    assert(convertedBackWeirdDay.month() == sc::July);
    assert(static_cast<unsigned int>(convertedBackWeirdDay.day()) == 14);

    auto day = sc::weekday{sysDate};
    assert(day == sc::Sunday);

    sc::sys_time now = sc::system_clock::now();
    sc::sys_seconds time = sc::floor<sc::seconds>(now);
    sc::sys_days date = sc::floor<sc::days>(now);

    auto date1 = 2024y / sc::May / 1d;
    auto date2 = date1 + sc::years{2}; // 2026/5/1
    assert(static_cast<int>(date2.year()) == 2026);
    auto date3 = date1 + sc::months{11}; // 2025/4/1
    assert(date3.month() == sc::April);

    for (auto date = 2024y / sc::June / 1d; date.month() == sc::June; date = sc::sys_days{date} + sc::days{1})
    {
        std::println("{} - {} - {}", date.year(), date.month(), date.day());
    }

    return 0;
}
