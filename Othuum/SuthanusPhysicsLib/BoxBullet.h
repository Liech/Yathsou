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
      virtual glm::vec3 getPosition()       override;
      virtual glm::mat4 getTransformation() override;
      virtual glm::vec3 getSize()           override;

    private:
      glm::vec3                _size;
      btDiscreteDynamicsWorld* _world;
      btRigidBody*             _body;
    };
  }
}