#include "vehicle/Vehicle.hpp"
#include <sstream>

std::string Describe(const Vehicle &vehicle)
{
    std::stringstream ss{};
    ss << vehicle.Brand() << "-" << vehicle.Model() << " is of price "
       << vehicle.Price() << "$";
    return ss.str();
}
