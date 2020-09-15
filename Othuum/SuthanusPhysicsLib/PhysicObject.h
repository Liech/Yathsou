#pragma once

#include <functional>
#include "IyathuumCoreLib/lib/glm/glm.hpp"
#include "IyathuumCoreLib/lib/glm/gtc/type_ptr.hpp"

namespace Suthanus
{
  class PhysicObject
  {
  public:
    virtual glm::vec3 getPosition       ()                    const = 0;
    virtual glm::mat4 getTransformation ()                    const = 0;
    virtual glm::quat getRotation       ()                    const = 0;
    virtual void      setVelocity       (glm::vec3)                 = 0;
    virtual void      setPosition       (glm::vec3)                 = 0;
    virtual void      setAngularVelocity(glm::vec3)                 = 0;
    virtual void      setRotation       (glm::quat)                 = 0;
    
    void setCollisionCallback(std::function<void(PhysicObject*)>);
    void collisionEvent      (PhysicObject* other);
  private:
    std::function<void(PhysicObject*)> _collsionCallback = [](PhysicObject*) {};
  };
}