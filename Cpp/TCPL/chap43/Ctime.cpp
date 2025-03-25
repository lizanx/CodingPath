#include <atomic>
#include <ctime>
#include <iostream>

namespace
{
    std::atomic_int counter{};
}

int main()
{
    // Calculate computing time.
    clock_t startClock = std::clock();
    for (int i{}; i < 1'000'000; ++i)
        ++counter;
    clock_t endClock = std::clock();
    std::cout << "Time consumption: "
              << (static_cast<double>(endClock - startClock) * 1000) / CLOCKS_PER_SEC
              << "ms.\n\n";

    // Date and time.
    time_t now = std::time(nullptr);
    tm *local_timeinfo = std::localtime(&now);
    tm *utc_timeinfo = std::gmtime(&now);
    std::cout << "Local time: " << std::asctime(local_timeinfo)
              << "UTC time: " << std::asctime(utc_timeinfo) << "\n";

    // From date/time to time point.
    time_t converted_local_now = std::mktime(local_timeinfo);
    time_t converted_utc_now = std::mktime(utc_timeinfo);
    std::cout << now << " / " << converted_local_now << " / " << converted_utc_now << "\n\n";

    // Calculate duration.
    tm date1{}, date2{};
    date1.tm_year = 2023;
    date1.tm_mon = 6;
    date1.tm_mday = 15;
    date2.tm_year = 2025;
    date2.tm_mon = 3;
    date2.tm_mday = 25;
    auto diff = std::difftime(mktime(&date2), mktime(&date1));
    std::cout << "Diff days: " << diff / (60 * 60 * 24) << "\n";
}
