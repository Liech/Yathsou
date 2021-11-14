#pragma once

#include <memory>
#include <string>
#include "IyathuumCoreLib/lib/glm/glm.hpp"

namespace Athanah {
  class Blueprint;
}

namespace Suthanus {
  class Box;
}

namespace Superb {
  class UnitConstructor;

  class Unit {
  public:
    Unit(const UnitConstructor& blueprint);

    glm::vec3                                 getPosition();
    glm::mat4                                 getTransformation();
    std::shared_ptr<Suthanus::Box>            getSelector();
    std::shared_ptr<Suthanus::Box>            getPhysic  ();
    std::shared_ptr<const Athanah::Blueprint> getBlueprint() const;
    std::string                               getID() const;

    void update();
  private:
    std::shared_ptr<Suthanus::Box>            _physic  ;
    std::shared_ptr<Suthanus::Box>            _selector;
    std::shared_ptr<const Athanah::Blueprint> _blueprint;    
    std::string                               _id;
  };
}