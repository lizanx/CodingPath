#include <chrono>
#include <print>
#include <string>

int main()
{
    namespace sc = std::chrono;
    using namespace std::chrono_literals;

    // Timezone database version
    std::string tzdbVersion = sc::remote_version();
    std::println("Timezone database version: {}", tzdbVersion);
    std::println("\n");

    // All valid timezones
    for (auto &zone : sc::get_tzdb().zones)
    {
        std::println("Timezone: {}", zone.name());
    }
    std::println("\n");

    // Suppose there's a meeting every Wednesday in March at 3:00pm in Prague.
    auto prague = sc::locate_zone("Europe/Prague");
    auto newyork = sc::locate_zone("America/New_York");
    sc::local_time meeting{sc::local_days{2026y / sc::March / sc::Wednesday[1]}};
    while (meeting < sc::local_days{2026y / sc::April / sc::Sunday[1]})
    {
        sc::zoned_time<sc::seconds> pragueLocal{prague, sc::local_days{meeting} + 15h};
        sc::zoned_time<sc::seconds> newyorkLocal{newyork, pragueLocal};
        std::println("Meeting at {} : {}", prague->name(), pragueLocal);
        std::println("Meeting at {} : {}", newyork->name(), newyorkLocal);
        meeting += sc::weeks{1};
    }
}
