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

    glm::vec3                                 getPosition()       const;
    float                                     getRotation()       const;
    glm::mat4                                 getTransformation() const;
    std::shared_ptr<Suthanus::Box>            getSelector()       const;
    std::shared_ptr<Suthanus::Box>            getPhysic  ()       const;
    std::shared_ptr<const Athanah::Blueprint> getBlueprint()      const;
    std::string                               getID()             const;

    void update();
  private:
    glm::vec3 getSidewardsTangent(glm::vec3 groundNormal) const;
    glm::vec3 getForwardTangent  (glm::vec3 groundNormal) const;
    bool placeOnGround();

    std::shared_ptr<Suthanus::Box>            _physic  ;
    std::shared_ptr<Suthanus::Box>            _selector;
    std::shared_ptr<const Athanah::Blueprint> _blueprint;    
    std::string                               _id;
  };
}