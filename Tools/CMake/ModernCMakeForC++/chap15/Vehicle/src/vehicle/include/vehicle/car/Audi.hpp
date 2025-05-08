#pragma once

#include "vehicle/Vehicle.hpp"

namespace Car
{

class Audi : public Vehicle
{
  public:
    ~Audi() override = default;
    std::string Brand() const override;
    std::string Model() const override;
    double Price() const override;

  protected:
    Audi(const std::string &model, double price);

  private:
    const std::string _brand{"Audi"};
    const std::string _model;
    const double _price;
};

class Audi_A6 : public Audi
{
  public:
    Audi_A6();
};

class Audi_S7 : public Audi
{
  public:
    Audi_S7();
};

} // namespace Car
