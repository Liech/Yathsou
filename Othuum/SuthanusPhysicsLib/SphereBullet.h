#pragma once

#include "Sphere.h"

class btRigidBody;
class btDiscreteDynamicsWorld;
namespace Suthanus
{
  namespace Bullet
  {
    class SphereBullet : public Sphere
    {
    public:
      SphereBullet(btDiscreteDynamicsWorld* world, glm::vec3 pos, float size, bool isDynamic = true);
      virtual glm::vec3 getPosition()              const override;
      virtual glm::mat4 getTransformation()        const override;
      virtual float     getRadius()                      override;
      virtual void      setPosition(glm::vec3 pos)       override;
      virtual void      setVelocity(glm::vec3 pos)       override;

    private:
      float                    _radius;
      btDiscreteDynamicsWorld* _world;
      btRigidBody* _body;
    };
  }
}