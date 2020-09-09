#pragma once

#include "Box.h"

class btRigidBody;
class btDiscreteDynamicsWorld;
namespace Suthanus
{
  namespace Bullet
  {
    class BoxBullet : public Box
    {
    public:
      BoxBullet(btDiscreteDynamicsWorld* world, glm::vec3 pos, glm::vec3 size, bool isDynamic = true);
      virtual glm::vec3 getPosition()              const override;
      virtual glm::mat4 getTransformation()        const override;
      virtual glm::vec3 getSize()                        override;
      virtual void      setPosition(glm::vec3 pos)       override;
      virtual void      setVelocity(glm::vec3 pos)       override;
      virtual void      setAngularVelocity(glm::vec3)    override;
      virtual void      setRotation(glm::vec3)           override;


    private:
      glm::vec3                _size;
      btDiscreteDynamicsWorld* _world;
      btRigidBody*             _body;
    };
  }
}