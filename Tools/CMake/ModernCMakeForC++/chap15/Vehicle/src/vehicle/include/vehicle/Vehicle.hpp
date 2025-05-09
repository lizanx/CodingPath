#pragma once

#include <string>

class Vehicle
{
  public:
    virtual ~Vehicle() = default;
    virtual std::string Brand() const = 0;
    virtual std::string Model() const = 0;
    virtual double Price() const = 0;
};
