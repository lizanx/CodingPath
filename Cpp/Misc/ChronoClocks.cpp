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
}

int main(int argc, char *argv[])
{
    ConversionBetweenSysClkAndTimet();

    return EXIT_SUCCESS;
}
