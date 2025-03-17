#include <chrono>
#include <iostream>

int main()
{
    auto now = std::chrono::system_clock::now();
    auto nowInSeconds = std::chrono::time_point_cast<std::chrono::seconds>(now);
    auto tomorrow = now + std::chrono::hours{24};

    std::cout << "Since epoch, it has been "
              << std::chrono::duration_cast<std::chrono::days>(now.time_since_epoch()).count()
              << "days, "
              << nowInSeconds.time_since_epoch().count()
              << " seconds.\n"
              << "For tomorrow, it'll be "
              << std::chrono::duration_cast<std::chrono::days>(tomorrow.time_since_epoch()).count()
              << "days.\n";
}
