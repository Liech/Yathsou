#pragma once

#include "Sphere.h"

class btRigidBody;
class btDiscreteDynamicsWorld;
class btDefaultMotionState;

namespace Suthanus
{
  class BulletCore;

  namespace Bullet
  {
    class SphereBullet : public Sphere
    {
    public:
      SphereBullet(PhysicEngine& engine, btDiscreteDynamicsWorld* world, glm::vec3 pos, float size, bool isDynamic = true);
      virtual ~SphereBullet();
      virtual glm::vec3 getPosition()               const override;
      virtual glm::mat4 getTransformation()         const override;
      virtual float     getRadius()                 const override;
      virtual glm::quat getRotation()               const override;
      virtual void      setPosition       (const glm::vec3& pos) override;
      virtual void      setVelocity       (const glm::vec3& pos) override;
      virtual void      setAngularVelocity(const glm::vec3& pos) override;
      virtual void      setRotation       (const glm::quat& rot) override;
      virtual void      addForce(const glm::vec3& force, const glm::vec3& offset) override;

    private:
      float                    _radius;
      btDiscreteDynamicsWorld* _world;
      btDefaultMotionState*    _motionState;
      btRigidBody*             _body;

      std::unique_ptr<BulletCore> _core;
    };
  }
}