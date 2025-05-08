#pragma once

#include "vehicle/Vehicle.hpp"

namespace Plane
{

enum class AirBusModel
{
    A320,
    A350
};

class AirBus : public Vehicle
{
  public:
    AirBus(AirBusModel model);
    std::string Brand() const override;
    VehicleType Type() const override;
    std::string Description() const override;

  private:
    AirBusModel _model;
};

} // namespace Plane
