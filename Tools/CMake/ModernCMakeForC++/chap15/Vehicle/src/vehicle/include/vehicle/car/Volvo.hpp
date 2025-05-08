#pragma once

#include "vehicle/Vehicle.hpp"

namespace Car
{

class Volvo : public Vehicle
{
  public:
    ~Volvo() override = default;
    std::string Brand() const override;
    std::string Model() const override;
    double Price() const override;

  protected:
    Volvo(const std::string &model, double price);

  private:
    const std::string _brand{"Volvo"};
    const std::string _model;
    const double _price;
};

class Volvo_S90 : public Volvo
{
  public:
    Volvo_S90();
};

class Volvo_XC90 : public Volvo
{
  public:
    Volvo_XC90();
};

} // namespace Car
