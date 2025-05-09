#include "vehicle/car/Audi.hpp"
#include <map>
#include <sstream>

std::string Car::Audi::Brand() const
{
    return _brand;
}

std::string Car::Audi::Model() const
{
    return _model;
}

double Car::Audi::Price() const
{
    return _price;
}

Car::Audi::Audi(const std::string &model, double price)
    : _model{model}, _price{price}
{
}

Car::Audi_A6::Audi_A6() : Audi("A6", 460'000)
{
}

Car::Audi_S7::Audi_S7() : Audi("S7", 620'000)
{
}
