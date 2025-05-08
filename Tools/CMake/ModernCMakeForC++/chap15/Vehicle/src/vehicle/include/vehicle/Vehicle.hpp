#pragma once

#include <string>

enum class VehicleType
{
    Land,
    Air,
    Water
};

class Vehicle
{
  public:
    virtual std::string Brand() const = 0;
    virtual VehicleType Type() const = 0;
    virtual std::string Description() const = 0;
    virtual ~Vehicle() = default;
};
