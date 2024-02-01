#include <iostream>
#include <chrono>

using namespace std::chrono;
using namespace std::literals::chrono_literals;
using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
    auto now = system_clock::now();
    auto time_since_epoch = now.time_since_epoch();
    cout << duration_cast<seconds>(time_since_epoch).count() << "s has elapsed since 1970/01/01 00:00:00" << endl;
    time_point<system_clock> next_christmas{
        duration_cast<seconds>(years(54)) +
        duration_cast<seconds>(months(11)) +
        duration_cast<seconds>(days(25)) };
    cout << "Days from next Christmas Day: " << duration_cast<days>(next_christmas - now).count() << endl;
}
