#include <chrono>
#include <iostream>
#include <string_view>
#include <thread>

namespace
{
    void PrintSeparationLine(std::string_view str)
    {
        std::print(std::cout, "===== {} =====\n", str);
    }

    void ConversionBetweenSysClkAndTimet()
    {
        PrintSeparationLine("SystemClock Start");

        auto sysClkNow = std::chrono::system_clock::now();
        std::cout << "System clock now: " << sysClkNow << "\n";
        time_t tnow = std::chrono::system_clock::to_time_t(sysClkNow);
        std::cout << "Time_t now(converted from system clock): " << std::ctime(&tnow) << "\n";
        std::cout << "\n";
        std::this_thread::sleep_for(std::chrono::seconds{2});
        tnow = std::time(nullptr);
        std::cout << "Time_t now: " << std::ctime(&tnow);
        sysClkNow = std::chrono::system_clock::from_time_t(tnow);
        std::cout << "System clock now(converted from time_t): " << sysClkNow << "\n";

        PrintSeparationLine("SystemClock End");
    }

    void ConversionBetweenUtcClkAndSysClk()
    {
        namespace sc = std::chrono;

        auto sysNow = sc::system_clock::now();
        std::cout << "System clock now: " << sysNow << "\n";
        auto utcNow = sc::clock_cast<sc::utc_clock>(sysNow);
        std::cout << "Utc clock now: " << utcNow << "\n";
        auto sysConvertedBack = sc::clock_cast<sc::system_clock>(utcNow);
        std::cout << "System clock(converted back): " << sysConvertedBack << "\n";
    }

    void ConversionOfDurations()
    {
        namespace sc = std::chrono;
        auto ms5499 = sc::microseconds{5499};
        std::cout << ms5499.count() << "us: round -> " << sc::round<sc::milliseconds>(ms5499).count() << "ms, "
                  << "floor -> " << sc::floor<sc::milliseconds>(ms5499).count() << "ms, "
                  << "ceil -> " << sc::ceil<sc::milliseconds>(ms5499).count() << "ms.\n";
        auto ms5500 = sc::microseconds{5500};
        std::cout << ms5500.count() << "us: round -> " << sc::round<sc::milliseconds>(ms5500).count() << "ms, "
                  << "floor -> " << sc::floor<sc::milliseconds>(ms5500).count() << "ms, "
                  << "ceil -> " << sc::ceil<sc::milliseconds>(ms5500).count() << "ms.\n";
    }
}

int main(int argc, char *argv[])
{
    ConversionBetweenSysClkAndTimet();

    std::cout << "\n============\n\n";

    ConversionBetweenUtcClkAndSysClk();

    std::cout << "\n============\n\n";

    ConversionOfDurations();

    return EXIT_SUCCESS;
}
