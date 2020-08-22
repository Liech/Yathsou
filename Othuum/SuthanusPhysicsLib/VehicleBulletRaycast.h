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

      float maxSteering()          override;
      void  setSteering(float)     override;
      float maxAcceleration()      override;
      void  setAcceleration(float) override;

    private:
      btDiscreteDynamicsWorld* _world    ;
      btRigidBody*             _body     ;
      btVehicleRaycaster*      _raycaster;
      btRaycastVehicle*        _vehicle  ;
      btRigidBody*             _chassis  ;

      btRigidBody* createChassisRigidBodyFromShape(btCollisionShape* chassisShape, btVector3 pos);
      void         addWheels(btVector3* halfExtents, btRaycastVehicle* vehicle, btRaycastVehicle::btVehicleTuning tuning);

      virtual glm::vec3 getPosition()       const override;
      virtual glm::mat4 getTransformation() const override;
    };
  }
}
