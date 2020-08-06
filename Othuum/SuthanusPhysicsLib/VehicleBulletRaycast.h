#pragma once

#include "Vehicle.h"

#include "lib/bullet/btBulletDynamicsCommon.h"

namespace Suthanus
{
  namespace Bullet
  {
    class VehicleBulletRaycast : public Vehicle
    {
    public:
      VehicleBulletRaycast(btDiscreteDynamicsWorld* world, glm::vec3 pos);
      glm::vec3 getSize();
      void forward();
    private:
      btDiscreteDynamicsWorld* _world    ;
      btRigidBody*             _body     ;
      btVehicleRaycaster*      _raycaster;
      btRaycastVehicle*        _vehicle  ;

      btRigidBody* createChassisRigidBodyFromShape(btCollisionShape* chassisShape);
      void         addWheels(btVector3* halfExtents, btRaycastVehicle* vehicle, btRaycastVehicle::btVehicleTuning tuning);

      virtual glm::vec3 getPosition()       override;
      virtual glm::mat4 getTransformation() override;
    };
  }
}
