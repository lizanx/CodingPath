#include "vehicle/car/Audi.hpp"
#include "vehicle/car/Volvo.hpp"
#include <gtest/gtest.h>

TEST(VehicleTest, AudiA6)
{
    using namespace std::string_literals;

    Car::Audi_A6 car{};
    EXPECT_EQ("Audi"s, car.Brand());
    EXPECT_EQ("A6"s, car.Model());
    EXPECT_EQ(460'000, car.Price());
}

TEST(VehicleTest, AudiS7)
{
    using namespace std::string_literals;

    Car::Audi_S7 car{};
    EXPECT_EQ("Audi"s, car.Brand());
    EXPECT_EQ("S7"s, car.Model());
    EXPECT_EQ(620'000, car.Price());
}

TEST(VehicleTest, VolvoS90)
{
    using namespace std::string_literals;

    Car::Volvo_S90 car{};
    EXPECT_EQ("Volvo"s, car.Brand());
    EXPECT_EQ("S90"s, car.Model());
    EXPECT_EQ(330'000, car.Price());
}

TEST(VehicleTest, VolvoXC90)
{
    using namespace std::string_literals;

    Car::Volvo_XC90 car{};
    EXPECT_EQ("Volvo"s, car.Brand());
    EXPECT_EQ("XC90"s, car.Model());
    EXPECT_EQ(390'000, car.Price());
}
