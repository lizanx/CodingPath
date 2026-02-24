#include <chrono>
#include <functional>
#include <iostream>
#include <vector>

namespace sc = std::chrono;

namespace
{
    struct Record
    {
        int Value;
        sc::system_clock::time_point CreatedAt;
    };

    std::vector<Record> Database{};
}

namespace ViaInheritance
{
    class Clock
    {
    public:
        virtual ~Clock() = default;
        virtual sc::system_clock::time_point Now() const = 0;
    };

    class RealClock : public Clock
    {
    public:
        sc::system_clock::time_point Now() const override
        {
            return sc::system_clock::now();
        }
    };

    class FakeClock : public Clock
    {
    public:
        FakeClock(sc::system_clock::time_point t) : _providedTimepoint{t}
        {
        }

        sc::system_clock::time_point Now() const override
        {
            return _providedTimepoint;
        }

    private:
        const sc::system_clock::time_point _providedTimepoint;
    };

    void Store(int value, Clock &clk)
    {
        Database.emplace_back(value, clk.Now());
    }
}

namespace ViaConcept
{
    template <typename Clk>
    concept ClockLike = sc::is_clock_v<Clk> && requires {
        { Clk::now() } -> std::same_as<sc::system_clock::time_point>;
    };

    class FakeClock
    {
    public:
        using rep = sc::system_clock::rep;
        using period = sc::system_clock::period;
        using duration = sc::system_clock::duration;
        using time_point = sc::system_clock::time_point;
        static constexpr bool is_steady = false;

        static time_point now()
        {
            return s_providedTimepoint;
        }

        void SetTimepoint(sc::system_clock::time_point t)
        {
            s_providedTimepoint = t;
        }

    private:
        static time_point s_providedTimepoint;
    };

    FakeClock::time_point FakeClock::s_providedTimepoint;

    void Store(int value, ClockLike auto clk)
    {
        Database.emplace_back(value, clk.now());
    }
}

namespace ViaLambda
{
    using TimeProvider = std::function<sc::system_clock::time_point()>;

    void Store(int value, TimeProvider timeProvider)
    {
        Database.emplace_back(value, timeProvider());
    }
}

namespace
{
    void TestClockViaInheritance()
    {
        int value = 1;
        auto clk = ViaInheritance::FakeClock{sc::system_clock::now()};
        ViaInheritance::Store(value, clk);
        if (auto record = Database.back(); record.Value != value || record.CreatedAt != clk.Now())
            std::cerr << "Failed: TestClockViaInheritance\n";
        else
            std::cout << "Success: TestClockViaInheritance" << std::endl;
    }

    void TestClockViaConcept()
    {
        int value = 2;
        auto clk = ViaConcept::FakeClock{};
        auto sysNow = sc::system_clock::now();
        clk.SetTimepoint(sysNow);
        ViaConcept::Store(value, clk);
        if (auto record = Database.back(); record.Value != value || record.CreatedAt != sysNow)
            std::cerr << "Failed: TestClockViaConcept\n";
        else
            std::cout << "Success: TestClockViaConcept" << std::endl;
    }

    void TestClockViaLambda()
    {
        int value = 3;
        auto sysNow = sc::system_clock::now();
        auto timeProvider = [sysNow]()
        {
            return sysNow;
        };
        ViaLambda::Store(value, timeProvider);
        if (auto record = Database.back(); record.Value != value || record.CreatedAt != sysNow)
            std::cerr << "Failed: TestClockViaLambda\n";
        else
            std::cout << "Success: TestClockViaLambda" << std::endl;
    }
}

int main()
{
    TestClockViaInheritance();
    TestClockViaConcept();
    TestClockViaLambda();

    return 0;
}
