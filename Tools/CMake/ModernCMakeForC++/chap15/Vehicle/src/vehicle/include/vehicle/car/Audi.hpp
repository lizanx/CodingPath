#pragma once

#include "vehicle/Vehicle.hpp"

namespace Car
{

enum class AudiModel
{
    A3,
    A4,
    A6,
    S7,
    A8
};

class Audi : public Vehicle
{
  public:
    Audi(AudiModel model);
    std::string Brand() const override;
    VehicleType Type() const override;
    std::string Description() const override;

  private:
    AudiModel _model;
};

} // namespace Car
