#pragma once

#include <memory>
#include <functional>
#include <map>
#include <set>
#include "IyathuumCoreLib/lib/glm/glm.hpp"
#include "IyathuumCoreLib/lib/glm/gtc/type_ptr.hpp"

namespace Suthanus
{
  class PhysicEngine;

  class PhysicObject
  {
  public:
    PhysicObject(PhysicEngine&);

    virtual ~PhysicObject() = default;
    virtual glm::vec3 getPosition       ()                    const = 0;
    virtual glm::mat4 getTransformation ()                    const = 0;
    virtual glm::quat getRotation       ()                    const = 0;
    virtual void      setVelocity       (glm::vec3)                 = 0;
    virtual void      setPosition       (glm::vec3)                 = 0;
    virtual void      setAngularVelocity(glm::vec3)                 = 0;
    virtual void      setRotation       (glm::quat)                 = 0;

    const std::set<std::shared_ptr<PhysicObject>>& currentContacts() const;
    glm::mat4 getRotationTransformation() const;
    std::weak_ptr<PhysicObject> self() { return _self; }

    //used by physic engine
    void initialize(std::weak_ptr<PhysicObject> self);
    void setCollisionCallback(std::function<void(std::weak_ptr<PhysicObject>)>);
    void collisionEventSecondPass(std::weak_ptr<PhysicObject> other);
    void collisionEventFirstPass (std::weak_ptr<PhysicObject> other);
    void clearContacts(); 

    PhysicEngine& engine();

  private:
    PhysicEngine& _engine;
    std::function<void(std::weak_ptr<PhysicObject>)> _collsionCallback = [](std::weak_ptr<PhysicObject>) {};
    std::weak_ptr<PhysicObject> _self;

    std::set<std::shared_ptr<PhysicObject>> _contacts;
  };
}