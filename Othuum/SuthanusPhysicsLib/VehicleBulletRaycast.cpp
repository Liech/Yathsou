#include "VehicleBulletRaycast.h"

#include "IyathuumCoreLib/lib/glm/gtc/type_ptr.hpp"

namespace Suthanus
{
  namespace Bullet
  {
    float VehicleBulletRaycast::maxAcceleration(){
      return 1000;
    }

    float VehicleBulletRaycast::maxSteering(){
      return 1;
    }

    void VehicleBulletRaycast::setAcceleration(float accel){
      _vehicle->applyEngineForce(accel, 2);
      _vehicle->applyEngineForce(accel, 3);
    }

    void VehicleBulletRaycast::setSteering(float steer) {
      _vehicle->setSteeringValue(btScalar(steer), 0);
      _vehicle->setSteeringValue(btScalar(steer), 1);
    }

    VehicleBulletRaycast::VehicleBulletRaycast(btDiscreteDynamicsWorld* world, glm::vec3 pos)
    {
      _world = world;
      btVector3 spawnPos = btVector3(pos[0], pos[1], pos[2]);
      btVector3 halfExtends(getSize()[0]/2.0,getSize()[1]/2.0,getSize()[2]/2.0f);
      btCollisionShape* chassisShape = new btBoxShape(halfExtends);
      btCompoundShape* compound = new btCompoundShape();
      btTransform localTransform;
      localTransform.setIdentity();
      localTransform.setOrigin(btVector3(0, 0,0));
      compound->addChildShape(localTransform, chassisShape);
      _chassis = this->createChassisRigidBodyFromShape(compound,spawnPos);
      _body = _chassis;
      _world->addRigidBody(_chassis);

      btVehicleRaycaster* vehicleRayCaster = new btDefaultVehicleRaycaster(_world);

      btRaycastVehicle::btVehicleTuning tuning;
      
      
      //Creates a new instance of the raycast vehicle
      _vehicle = new btRaycastVehicle(tuning, _chassis, vehicleRayCaster);

      //Never deactivate the vehicle
      _chassis->setActivationState(DISABLE_DEACTIVATION);

      //Adds the vehicle to the world
      _world->addVehicle(_vehicle);

      //Adds the wheels to the vehicle
      addWheels(&halfExtends, _vehicle, tuning);
    }


    void VehicleBulletRaycast::addWheels(
      btVector3* halfExtents,
      btRaycastVehicle* vehicle,
      btRaycastVehicle::btVehicleTuning tuning)
    {
      //The direction of the raycast, the btRaycastVehicle uses raycasts instead of simiulating the wheels with rigid bodies
      btVector3 wheelDirectionCS0(0, -1, 0);

      //The axis which the wheel rotates arround
      btVector3 wheelAxleCS(-1, 0, 0);

      btScalar suspensionRestLength(0.2);

      btScalar wheelWidth(0.4);

      btScalar wheelRadius(0.2);

      //The height where the wheels are connected to the chassis
      btScalar connectionHeight(-halfExtents->y() *0.9);

      //All the wheel configuration assumes the vehicle is centered at the origin and a right handed coordinate system is used
      btVector3 wheelConnectionPoint(halfExtents->x(), connectionHeight, halfExtents->z());

      //Adds the front wheels
      vehicle->addWheel(wheelConnectionPoint, wheelDirectionCS0, wheelAxleCS, suspensionRestLength, wheelRadius, tuning, true);

      vehicle->addWheel(wheelConnectionPoint * btVector3(-1, 1, 1), wheelDirectionCS0, wheelAxleCS, suspensionRestLength, wheelRadius, tuning, true);

      //Adds the rear wheels
      vehicle->addWheel(wheelConnectionPoint * btVector3(1, 1, -1), wheelDirectionCS0, wheelAxleCS, suspensionRestLength, wheelRadius, tuning, false);

      vehicle->addWheel(wheelConnectionPoint * btVector3(-1, 1, -1), wheelDirectionCS0, wheelAxleCS, suspensionRestLength, wheelRadius, tuning, false);

      //Configures each wheel of our vehicle, setting its friction, damping compression, etc.
      //For more details on what each parameter does, refer to the docs
      for (int i = 0; i < vehicle->getNumWheels(); i++)
      {
        btWheelInfo& wheel = vehicle->getWheelInfo(i);
        wheel.m_suspensionStiffness = 50;
        wheel.m_wheelsDampingCompression = btScalar(0.3) * 2 * btSqrt(wheel.m_suspensionStiffness);//btScalar(0.8);
        wheel.m_wheelsDampingRelaxation = btScalar(0.5) * 2 * btSqrt(wheel.m_suspensionStiffness);//1;
        //Larger friction slips will result in better handling
        wheel.m_frictionSlip = btScalar(1.2);
        wheel.m_rollInfluence = 1;
      }
    }

    btRigidBody* VehicleBulletRaycast::createChassisRigidBodyFromShape(btCollisionShape* chassisShape, btVector3 pos)
    {
      btTransform chassisTransform;
      chassisTransform.setIdentity();
      chassisTransform.setOrigin(pos);

      {
        //chassis mass 
        btScalar mass(1200);

        //since it is dynamic, we calculate its local inertia
        btVector3 localInertia(0, 0, 0);
        chassisShape->calculateLocalInertia(mass, localInertia);

        //using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
        btDefaultMotionState* groundMotionState = new btDefaultMotionState(chassisTransform);
        btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, groundMotionState, chassisShape, localInertia);

        return new btRigidBody(rbInfo);
      }
    }

    glm::vec3 VehicleBulletRaycast::getPosition() const
    {
      auto trans = _body->getWorldTransform().getOrigin();
      return glm::vec3(trans[0], trans[1], trans[2]);
    }

    glm::mat4 VehicleBulletRaycast::getTransformation() const
    {
      glm::mat4 result;
      btTransform trans = _body->getWorldTransform();
      float mat[16];
      trans.getOpenGLMatrix(mat);
      return glm::make_mat4(mat);
    }

    glm::vec3 VehicleBulletRaycast::getSize()
    {
      return glm::vec3(0.4, 0.4, 1);
    }
  }
}