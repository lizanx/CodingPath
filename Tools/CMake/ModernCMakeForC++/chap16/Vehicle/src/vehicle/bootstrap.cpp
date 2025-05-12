#include "vehicle/car/Audi.hpp"
#include "vehicle/car/Volvo.hpp"
#include <iostream>
#include <sstream>

namespace
{

std::string Describe(const Vehicle &vehicle)
{
    std::stringstream ss{};
    ss << vehicle.Brand() << "-" << vehicle.Model() << " is of price "
       << vehicle.Price() << "$";
    return ss.str();
}

} // namespace

void bootstrap()
{
    std::cout << ::Describe(Car::Audi_A6{}) << "\n";
    std::cout << ::Describe(Car::Audi_S7{}) << "\n";
    std::cout << ::Describe(Car::Volvo_S90{}) << "\n";
    std::cout << ::Describe(Car::Volvo_XC90{}) << "\n";
}
