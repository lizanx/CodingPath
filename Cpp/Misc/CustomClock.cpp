#include <chrono>
#include <cstdint>
#include <iostream>

namespace
{
    namespace sc = std::chrono;

    class ManualClock
    {
    public:
        using rep = std::int64_t;
        using period = std::nano;
        using duration = sc::duration<rep, period>;
        using time_point = sc::time_point<ManualClock>;

        static time_point now() noexcept
        {
            return _current;
        }

        static constexpr bool is_steady = true;

        static void advance(duration d) noexcept
        {
            _current += d;
        }

    private:
        static time_point _current;
    };

    ManualClock::time_point ManualClock::_current{duration{0}};

    class ScaleClock
    {
    public:
        using rep = std::int64_t;
        using period = std::nano;
        using duration = sc::duration<rep, period>;
        using time_point = sc::time_point<ScaleClock>;

        static time_point now() noexcept
        {
            auto steadyNow = sc::steady_clock::now();
            auto durationSinceEpoch = sc::duration_cast<duration>(steadyNow.time_since_epoch());
            return time_point{duration{static_cast<rep>(durationSinceEpoch.count() * _multiplier)}};
        }

        static constexpr bool is_steady = false;

        static void SetScale(double multiplier) noexcept
        {
            _multiplier = multiplier;
        }

    private:
        static double _multiplier;
    };

    double ScaleClock::_multiplier{1.0};
}

int main()
{
    using namespace std::chrono_literals;

    static_assert(sc::is_clock_v<ManualClock>);
    auto t1 = ManualClock::now();
    ManualClock::advance(500ms);
    auto t2 = ManualClock::now();
    std::cout << "t2 - t1 = " << sc::duration_cast<sc::milliseconds>(t2 - t1).count() << "ms\n";

    static_assert(sc::is_clock_v<ScaleClock>);
    auto steadyNow = sc::steady_clock::now();
    ScaleClock::SetScale(2.0);
    auto scaledNow = ScaleClock::now();
    std::cout << "Steady time since epoch: " << steadyNow.time_since_epoch().count() << "\n"
              << "ScaleClock time since epoch: " << scaledNow.time_since_epoch().count() << "\n";
}
