#include <cstdio>
#include <functional>
#include <stdexcept>
// #include <limits>

using namespace std;

struct SpeedUpdate
{
    double velocity_mps;
};

struct CarDetected
{
    double distance_m;
    double velocity_mps;
};

struct SpeedLimitDetected
{
    unsigned short speed_mps;
};

struct BreakCommand
{
    double time_to_collision_s;
};

typedef function<void(const SpeedUpdate &)> SpeedUpdateCallback;
typedef function<void(const CarDetected &)> CarDetectedCallback;
using SpeedLimitCallback = function<void(const SpeedLimitDetected &)>;

struct IServiceBus
{
    virtual ~IServiceBus() = default;
    virtual void publish(const BreakCommand &) = 0;
    virtual void subscribe(SpeedUpdateCallback) = 0;
    virtual void subscribe(CarDetectedCallback) = 0;
    virtual void subscribe(SpeedLimitCallback) = 0;
};

struct MockServiceBus : IServiceBus
{
    void publish(const BreakCommand &cmd) override
    {
        commands_published++;
        last_command = cmd;
    };
    void subscribe(SpeedUpdateCallback callback) override
    {
        speed_update_callback = callback;
    };
    void subscribe(CarDetectedCallback callback) override
    {
        car_detected_callback = callback;
    };
    virtual void subscribe(SpeedLimitCallback callback) override
    {
        speed_limit_update_callback = callback;
    }
    BreakCommand last_command{};
    int commands_published{};
    SpeedUpdateCallback speed_update_callback{};
    CarDetectedCallback car_detected_callback{};
    SpeedLimitCallback speed_limit_update_callback{};
};

struct AutoBrake
{
    AutoBrake(IServiceBus &bus)
        : collision_threshold_s{5}, speed_mps{}, speed_limit_mps{39}
    {
        bus.subscribe([this, &bus](const SpeedUpdate &update)
                    {
                        speed_mps = update.velocity_mps;
                        if (speed_mps > speed_limit_mps)
                            bus.publish(BreakCommand{0});
                    });
        bus.subscribe([this, &bus](const CarDetected &cd)
                    {
                        auto relative_velocity_mps = speed_mps - cd.velocity_mps;
                        auto time_to_collision_s = cd.distance_m / relative_velocity_mps;
                        if(time_to_collision_s > 0 && time_to_collision_s <= collision_threshold_s) {
                            bus.publish(BreakCommand{ time_to_collision_s });
                        }
                    });
        bus.subscribe([this, &bus](const SpeedLimitDetected &sld)
                            {
                                set_speed_limit_mps(sld.speed_mps);
                                if (get_speed_mps() > get_speed_limit_mps())
                                {
                                    bus.publish(BreakCommand{0.0});
                                }
                            });
    }
    void set_collision_threshold_s(double x)
    {
        if (x < 1)
            throw runtime_error{"Collision less than 1."};
        collision_threshold_s = x;
    }
    double get_collision_threshold_s() const
    {
        return collision_threshold_s;
    }
    double get_speed_mps() const
    {
        return speed_mps;
    }
    unsigned short get_speed_limit_mps() const
    {
        return speed_limit_mps;
    }
    void set_speed_limit_mps(const unsigned short &limit)
    {
        speed_limit_mps = limit;
    }

private:
    double collision_threshold_s;
    double speed_mps;
    unsigned short speed_limit_mps;
};

void assert_that(bool statement, const char *message)
{
    if (!statement)
        throw runtime_error(message);
}

int run_test(void (*unit_test)(), const char *name)
{
    try
    {
        unit_test();
        printf("[+] Test %s successful.\n", name);
        return 0;
    }
    catch (const exception &e)
    {
        printf("[-] Test failure in %s. %s.\n", name, e.what());
    }
    return -1;
}

void initial_speed_is_zero()
{
    MockServiceBus bus{};
    AutoBrake auto_break{bus};
    assert_that(auto_break.get_speed_mps() == 0, "speed not equal 0");
}

void initial_speed_limit_is_39()
{
    MockServiceBus bus{};
    AutoBrake auto_brake{bus};
    assert_that(auto_brake.get_speed_limit_mps() == 39, "speed limit not equal to 39");
}

void initial_sensitivity_is_five()
{
    MockServiceBus bus{};
    AutoBrake auto_break{bus};
    assert_that(auto_break.get_collision_threshold_s() == 5, "sensitivity is not 5");
}

void sensitivity_greater_than_1()
{
    MockServiceBus bus{};
    AutoBrake auto_break{bus};
    try
    {
        auto_break.set_collision_threshold_s(0.5L);
    }
    catch (const exception &)
    {
        return;
    }
    assert_that(false, "no exception thrown");
}

void speed_is_saved()
{
    MockServiceBus bus{};
    AutoBrake auto_break{bus};

    bus.speed_update_callback(SpeedUpdate{100L});
    assert_that(100L == auto_break.get_speed_mps(), "speed was not saved to 100");
    bus.speed_update_callback(SpeedUpdate{50L});
    assert_that(50L == auto_break.get_speed_mps(), "speed was not saved to 50");
    bus.speed_update_callback(SpeedUpdate{0L});
    assert_that(0L == auto_break.get_speed_mps(), "speed was not saved to 0");
}

void speed_limit_is_saved()
{
    MockServiceBus bus{};
    AutoBrake brake{bus};

    bus.speed_limit_update_callback(SpeedLimitDetected{0});
    assert_that(0 == brake.get_speed_limit_mps(), "speed was not saved to 0");
    bus.speed_limit_update_callback(SpeedLimitDetected{50});
    assert_that(50 == brake.get_speed_limit_mps(), "speed was not saved to 50");
    bus.speed_limit_update_callback(SpeedLimitDetected{100});
    assert_that(100 == brake.get_speed_limit_mps(), "speed was not saved to 100");
}

void no_alert_when_not_imminent()
{
    MockServiceBus bus{};
    AutoBrake auto_break{bus};
    auto_break.set_collision_threshold_s(2L);
    bus.speed_update_callback(SpeedUpdate{30L});
    bus.car_detected_callback(CarDetected{1000L, 50L});
    assert_that(bus.commands_published == 0, "break commands were published");
}

void no_alert_when_within_limit()
{
    MockServiceBus bus{};
    AutoBrake brake{bus};

    bus.speed_update_callback(SpeedUpdate{34L});
    bus.speed_limit_update_callback(SpeedLimitDetected{35});
    assert_that(bus.commands_published == 0, "brake commands were published");
}

void alert_when_imminent()
{
    MockServiceBus bus{};
    AutoBrake auto_break{bus};
    auto_break.set_collision_threshold_s(10L);
    bus.speed_update_callback(SpeedUpdate{30L});
    bus.car_detected_callback(CarDetected{30L, 0L});
    assert_that(bus.commands_published == 1, "1 break command was not published");
    assert_that(bus.last_command.time_to_collision_s == 1L,
                "time to collision"
                "not computed correctly.");
}

void alert_when_exceed_limit()
{
    MockServiceBus bus{};
    AutoBrake brake{bus};

    bus.speed_limit_update_callback(SpeedLimitDetected{35});
    bus.speed_update_callback(SpeedUpdate{40L});
    assert_that(bus.commands_published == 1, "1 brake command was not published");
    assert_that(bus.last_command.time_to_collision_s == 0L, "time to collisioin not computed correctly");
}

void alert_when_speed_update_exceed_limit()
{
    MockServiceBus bus{};
    AutoBrake brake{bus};

    bus.speed_limit_update_callback(SpeedLimitDetected{35});
    bus.speed_update_callback(SpeedUpdate{30L});
    bus.speed_limit_update_callback(SpeedLimitDetected{25});
    assert_that(bus.commands_published == 1, "1 brake command was not published");
    assert_that(bus.last_command.time_to_collision_s == 0L, "time to collisioin not computed correctly");
}

int main()
{
    run_test(initial_speed_is_zero, "initial speed is 0");
    run_test(initial_speed_limit_is_39, "initial speed limit is 39");
    run_test(initial_sensitivity_is_five, "initial sensitivity is 5");
    run_test(sensitivity_greater_than_1, "sensitivity greater than 1");
    run_test(speed_is_saved, "speed is saved");
    run_test(speed_limit_is_saved, "speed limit is saved");
    run_test(no_alert_when_not_imminent, "no alert when not imminent");
    run_test(no_alert_when_within_limit, "no alert when within limit");
    run_test(alert_when_imminent, "alert when imminent");
    run_test(alert_when_exceed_limit, "alert when exceed limit");
    run_test(alert_when_speed_update_exceed_limit, "alert when speed update exceed limit");
}
