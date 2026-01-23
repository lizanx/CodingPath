#include <chrono>
#include <iostream>

int main()
{
    namespace sc = std::chrono;
    using namespace std::chrono_literals;

    const auto &timezoneDb = sc::get_tzdb();
    const auto *parisTz = timezoneDb.locate_zone("Europe/Paris");
    if (!parisTz)
    {
        std::cerr << "Failed to get time zone of Paris\n";
        exit(-1);
    }
    auto sysNow = sc::system_clock::now();
    auto parisLocalNow = parisTz->to_local(sysNow);
    auto sysNowConvertedFromParisLocal = parisTz->to_sys(parisLocalNow);
    std::cout << "Sys now: " << sysNow << '\n'
              << "Paris local now: " << parisLocalNow << '\n'
              << "Sys now(converted back from Paris local time): " << sysNowConvertedFromParisLocal << "\n\n";

    sc::local_time pastTime{sc::local_days{2025y / 3 / 23} + 9h};
    const sc::zoned_time pastTimeParis{parisTz, pastTime};
    const auto pastTimeSys = parisTz->to_sys(pastTime);
    std::cout << "Local past: " << sc::zoned_time{sc::current_zone(), pastTime} << '\n'
              << "Paris past: " << pastTimeParis << '\n'
              << "Sys past: " << pastTimeSys << '\n';

    return 0;
}
