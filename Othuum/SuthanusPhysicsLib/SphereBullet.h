#pragma once

#include "Sphere.h"

class btRigidBody;
class btDiscreteDynamicsWorld;
class btDefaultMotionState;

namespace Suthanus
{
  namespace Bullet
  {
    class SphereBullet : public Sphere
    {
    public:
      SphereBullet(btDiscreteDynamicsWorld* world, glm::vec3 pos, float size, bool isDynamic = true);
      ~SphereBullet();
      virtual glm::vec3 getPosition()               const override;
      virtual glm::mat4 getTransformation()         const override;
      virtual float     getRadius()                 const override;
      virtual glm::quat getRotation()               const override;
      virtual void      setPosition(glm::vec3 pos)        override;
      virtual void      setVelocity(glm::vec3 pos)        override;
      virtual void      setAngularVelocity(glm::vec3 pos) override;
      virtual void      setRotation(glm::quat rot)        override;

    private:
      float                    _radius;
      btDiscreteDynamicsWorld* _world;
      btDefaultMotionState*    _motionState;
      btRigidBody*             _body;
    };
  }
}