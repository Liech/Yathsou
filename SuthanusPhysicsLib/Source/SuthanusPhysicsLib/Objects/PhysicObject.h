#pragma once

#include <memory>
#include <functional>
#include <map>
#include <set>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Suthanus
{
  class PhysicEngine;

  class PhysicObject
  {
  public:
    PhysicObject(PhysicEngine&);

    virtual ~PhysicObject() = default;
    virtual glm::vec3 getPosition       ()                           const = 0;
    virtual glm::mat4 getTransformation ()                           const = 0;
    virtual glm::quat getRotation       ()                           const = 0;
    virtual void      setVelocity       (const glm::vec3&)                 = 0;
    virtual void      setPosition       (const glm::vec3&)                 = 0;
    virtual void      setAngularVelocity(const glm::vec3&)                 = 0;
    virtual void      setRotation       (const glm::quat&)                 = 0;
    virtual void      addForce(const glm::vec3& force, const glm::vec3& offset) = 0;

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