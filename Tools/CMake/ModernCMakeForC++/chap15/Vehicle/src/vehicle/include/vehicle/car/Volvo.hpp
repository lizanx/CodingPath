#pragma once

#include "vehicle/Vehicle.hpp"

namespace Car
{

enum class VolvoModel
{
    S60,
    S90,
    XC60,
    XC90
};

class Volvo : public Vehicle
{
  public:
    Volvo(VolvoModel model);
    std::string Brand() const override;
    VehicleType Type() const override;
    std::string Description() const override;

  private:
    VolvoModel _model;
};

} // namespace Car
