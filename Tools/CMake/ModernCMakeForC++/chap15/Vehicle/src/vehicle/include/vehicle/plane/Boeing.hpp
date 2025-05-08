#pragma once

#include "vehicle/Vehicle.hpp"

namespace Plane
{

enum class BoeingModel
{
    BOE737,
    BOE747
};

class Boeing : public Vehicle
{
  public:
    Boeing(BoeingModel model);
    std::string Brand() const override;
    VehicleType Type() const override;
    std::string Description() const override;

  private:
    BoeingModel _model;
};

} // namespace Plane
