#include "VehicleDriver.h"

namespace Suthanus
{
  VehicleDriver::VehicleDriver(const Vehicle& vehicle):
    _vehicle(vehicle),
    _target(vehicle.getPosition())
  {
  }

  void VehicleDriver::setTarget(glm::vec3 target)
  {
    _target = target;
  }

  void VehicleDriver::setBrake(bool brakeEnabled)
  {
    _brake = brakeEnabled;
  }

  void VehicleDriver::update()
  {
    //const glm::vec3 rotationAxis = ;
  } 

  glm::vec3 VehicleDriver::getRotationAxis()
  {
    //_vehicle.getTransformation()
    return glm::vec3();
  }
}