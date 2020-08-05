#pragma once

#include "Vehicle.h"

class btRigidBody;
class btDiscreteDynamicsWorld;

namespace Suthanus
{
  namespace Bullet
  {
    class VehicleBulletRaycast : public Vehicle
    {
    public:
      VehicleBulletRaycast(btDiscreteDynamicsWorld* world, glm::vec3 pos);
      glm::vec3 getSize();
    private:
      btDiscreteDynamicsWorld* _world;
      btRigidBody* _body;

      // Geerbt über Vehicle
      virtual glm::vec3 getPosition() override;
      virtual glm::mat4 getTransformation() override;
    };
  }
}