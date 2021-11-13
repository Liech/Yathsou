#pragma once

#include <memory>
#include <string>
#include "IyathuumCoreLib/lib/glm/glm.hpp"

namespace Suthanus {
  class Box;
}

namespace Superb {
  class UnitConstructor;

  class Unit {
  public:
    Unit(const UnitConstructor& blueprint);

    glm::vec3                      getPosition();
    std::shared_ptr<Suthanus::Box> getSelector();

    void update();
  private:
    std::shared_ptr<Suthanus::Box> _physic  ;
    std::shared_ptr<Suthanus::Box> _selector;
  };
}