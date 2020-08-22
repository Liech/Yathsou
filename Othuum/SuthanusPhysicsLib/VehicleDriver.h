#pragma once

#include "IyathuumCoreLib/lib/glm/glm.hpp"
#include "Vehicle.h"

namespace Suthanus
{
  class VehicleDriver
  {
  public:
    VehicleDriver(const Vehicle&);

    void setTarget(glm::vec3 target);
    void setBrake(bool braking);
    void update();

  private:
    const Vehicle& _vehicle;
    glm::vec3      _target ;
    bool           _brake   = true;
  };
}