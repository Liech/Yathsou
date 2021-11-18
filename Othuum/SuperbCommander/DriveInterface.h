#pragma once

#include <memory>
#include "AhwassaGraphicsLib/Input/Input.h"

namespace Suthanus {
  class PhysicObject;
}

namespace Superb {
  class DriveInterface {
  public:
    DriveInterface(Ahwassa::Input& input);

    void setTarget(std::shared_ptr<Suthanus::PhysicObject>);
    void update();
  private:
    std::shared_ptr<Suthanus::PhysicObject> _target = nullptr;
    Ahwassa::Input&                         _input;
  };
}