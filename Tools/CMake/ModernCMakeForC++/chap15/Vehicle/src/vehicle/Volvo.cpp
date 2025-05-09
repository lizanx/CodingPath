#include "vehicle/car/Volvo.hpp"
#include <map>
#include <sstream>

std::string Car::Volvo::Brand() const
{
    return _brand;
}

std::string Car::Volvo::Model() const
{
    return _model;
}

double Car::Volvo::Price() const
{
    return _price;
}

Car::Volvo::Volvo(const std::string &model, double price)
    : _model{model}, _price{price}
{
}

Car::Volvo_S90::Volvo_S90() : Volvo("S90", 330'000)
{
}

Car::Volvo_XC90::Volvo_XC90() : Volvo("XC90", 390'000)
{
}
