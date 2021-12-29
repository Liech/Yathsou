#pragma once

#include "Vehicle.h"

#include "SuthanusPhysicsLib/lib/bullet/btBulletDynamicsCommon.h"

namespace Suthanus
{
  namespace Bullet
  {
    class VehicleBulletRaycast : public Vehicle
    {
    public:
      VehicleBulletRaycast(btDiscreteDynamicsWorld* world, glm::vec3 pos);
      ~VehicleBulletRaycast();
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

      btRigidBody* createChassisRigidBodyFromShape(btCollisionShape* chassisShape, btVector3 pos);
      void         addWheels(btVector3* halfExtents, btRaycastVehicle* vehicle, btRaycastVehicle::btVehicleTuning tuning);

      virtual glm::vec3 getPosition()              const override;
      virtual glm::mat4 getTransformation()        const override;
      virtual void      setPosition(glm::vec3 pos)       override;
      virtual glm::quat getRotation()              const override;
      virtual void      setVelocity(glm::vec3 pos)       override;
      virtual void      setAngularVelocity(glm::vec3)    override;
      virtual void      setRotation(glm::quat)           override;
    };
  }
}
