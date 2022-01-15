#pragma once

#include <memory>
#include "AhwassaGraphicsLib/Input/Input.h"

namespace Suthanus {
  class PhysicObject;
}

namespace Superb {
  class Unit;

  class DriveInterface {
  public:
    DriveInterface(Ahwassa::Input& input);

    void setTarget(std::shared_ptr<Unit>);
    void update();
  private:
    std::shared_ptr<Unit> _target = nullptr;
    Ahwassa::Input&                         _input;
  };
}