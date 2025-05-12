#include "vehicle/car/Audi.hpp"
#include "vehicle/car/Volvo.hpp"
#include <fmt/format.h>

namespace
{

std::string Describe(const Vehicle &vehicle)
{
    return fmt::format("{}-{} is of price {}$", vehicle.Brand(),
                       vehicle.Model(), vehicle.Price());
}

} // namespace

void bootstrap()
{
    fmt::print("fmt::print\t{}\n", Describe(Car::Audi_A6{}));
    fmt::print("fmt::print\t{}\n", Describe(Car::Audi_S7{}));
    fmt::print("fmt::print\t{}\n", Describe(Car::Volvo_S90{}));
    fmt::print("fmt::print\t{}\n", Describe(Car::Volvo_XC90{}));
}
