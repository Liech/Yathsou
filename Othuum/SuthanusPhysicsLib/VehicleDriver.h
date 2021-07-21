#pragma once

#include "IyathuumCoreLib/lib/glm/glm.hpp"
#include "Objects/Vehicle.h"

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
    glm::vec3       getRotationAxis();

    const Vehicle& _vehicle;
    glm::vec3      _target ;
    bool           _brake   = true;
  };
}