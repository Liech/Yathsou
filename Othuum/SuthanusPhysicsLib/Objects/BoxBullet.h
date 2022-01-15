#pragma once

#include "Box.h"

class btRigidBody;
class btDiscreteDynamicsWorld;
class btDefaultMotionState;

namespace Suthanus
{
  class BulletCore;
  class PhysicEngine;

  namespace Bullet
  {
    class BoxBullet : public Box
    {
    public:
      BoxBullet(PhysicEngine& engine, btDiscreteDynamicsWorld* world, glm::vec3 pos, glm::vec3 size, bool isDynamic = true);
      ~BoxBullet();
      virtual glm::vec3 getPosition()                            const override;
      virtual glm::mat4 getTransformation()                      const override;
      virtual glm::vec3 getSize()                                      override;
      virtual glm::quat getRotation()                            const override;
      virtual void      setPosition       (const glm::vec3& pos)       override;
      virtual void      setVelocity       (const glm::vec3& pos)       override;
      virtual void      setAngularVelocity(const glm::vec3&)           override;
      virtual void      setRotation       (const glm::quat&)           override;
      virtual void      addForce(const glm::vec3& force, const glm::vec3& offset) override;


    private:
      glm::vec3                _size;
      btDiscreteDynamicsWorld* _world;
      btDefaultMotionState*    _motionState;
      btRigidBody*             _body;

      std::unique_ptr<BulletCore> _core;
    };
  }
}