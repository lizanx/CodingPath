#include <chrono>
#include <iostream>
#include <type_traits>

namespace
{
    using std::chrono::high_resolution_clock;
    using std::chrono::steady_clock;
    using std::chrono::system_clock;

    void ShowInfoAboutHighResolutionClock()
    {
        using std::cout;
        cout << std::boolalpha;
        cout << "High-resolution clock is stead? - " << high_resolution_clock::is_steady << "\n";
        cout << "high_resolution_clk == system_clk? - " << std::is_same_v<high_resolution_clock, system_clock> << "\n";
        cout << "high_resolution_clk == stead_clk? - " << std::is_same_v<high_resolution_clock, steady_clock> << "\n";
    }
}

int main(int argc, char *argv[])
{
    ShowInfoAboutHighResolutionClock();

    return 0;
}
