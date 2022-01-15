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

    void move(const glm::vec2& direction);
    void rotate(const float& radian);

    void update();
  private:
    glm::vec3 getForwards(glm::vec3 groundNormal) const;
    glm::vec3 getSidewards  (glm::vec3 groundNormal) const;
    bool placeOnGround();

    float                                     _rotation = 0;
    std::shared_ptr<Suthanus::Box>            _physic  ;
    std::shared_ptr<Suthanus::Box>            _selector;
    std::shared_ptr<const Athanah::Blueprint> _blueprint;    
    std::string                               _id;
  };
}