#pragma once

#include <memory>
#include <functional>
#include "IyathuumCoreLib/lib/glm/glm.hpp"
#include "IyathuumCoreLib/lib/glm/gtc/type_ptr.hpp"

namespace Suthanus
{
  class PhysicObject
  {
  public:
    virtual ~PhysicObject();
    virtual glm::vec3 getPosition       ()                    const = 0;
    virtual glm::mat4 getTransformation ()                    const = 0;
    virtual glm::quat getRotation       ()                    const = 0;
    virtual void      setVelocity       (glm::vec3)                 = 0;
    virtual void      setPosition       (glm::vec3)                 = 0;
    virtual void      setAngularVelocity(glm::vec3)                 = 0;
    virtual void      setRotation       (glm::quat)                 = 0;

    glm::mat4 getRotationTransformation() const;
    std::weak_ptr<PhysicObject> self() { return _self; }

    void initialize(std::weak_ptr<PhysicObject> self);
    void setCollisionCallback(std::function<void(std::weak_ptr<PhysicObject>)>);
    void collisionEvent      (std::weak_ptr<PhysicObject> other);

    bool isDisposed() const;
    virtual void dispose();
  private:
    std::function<void(std::weak_ptr<PhysicObject>)> _collsionCallback = [](std::weak_ptr<PhysicObject>) {};
    std::weak_ptr<PhysicObject> _self;
    bool                        _deleted = false;
  };
}