#pragma once

#include "Vehicle.h"

class btRigidBody;
class btDiscreteDynamicsWorld;
class btVehicleRaycaster;
class btRaycastVehicle;

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
      btDiscreteDynamicsWorld* _world    ;
      btRigidBody*             _body     ;
      btVehicleRaycaster*      _raycaster;
      btRaycastVehicle*        _vehicle  ;

      // Geerbt �ber Vehicle
      virtual glm::vec3 getPosition() override;
      virtual glm::mat4 getTransformation() override;
    };
  }
}

/*
void OgrewithCeguiApp::CreateCar(void) {
Entity *Carent;
Ogre::Vector3 vrre;
Ogre::Entity* mWheels[4];
Ogre::SceneNode* mWheelNodes[4];
Ogre::SceneNode *node;
Ogre::SceneNode *carnode;
btCollisionShape* chassisShape;
btCompoundShape* compound;
btTransform localTrans;
btVector3 localInertia(0,0,0);
CarMotionState *motionstate;
btRigidBody* body ;
btRaycastVehicle::btVehicleTuning mTuning;
btVehicleRaycaster* m_vehicleRayCaster;
btRaycastVehicle* m_vehicle;
btVector3 wheelDirectionCS0(0,-1,0);
btVector3 wheelAxleCS(-1,0,0);
float wheelWidth=42.0;
float connectionHeight=40.0;
float wheelRadius=63.0;
float suspensionRestLength=0.6;
bool isFrontWheel;

mTuning.m_frictionSlip=10.5;
mTuning.m_maxSuspensionTravelCm=500.0;
mTuning.m_suspensionCompression=4.4;
mTuning.m_suspensionDamping=2.3;
mTuning.m_suspensionStiffness=20.0;

Carent = mSceneMgr->createEntity("roof1", "roof1.mesh");
Carent->setVisible(false);
node=mSceneMgr->getRootSceneNode()->createChildSceneNode();
carnode=node->createChildSceneNode("carnode");
carnode->attachObject(Carent);

vrre=Carent->getBoundingBox().getHalfSize();


//419 178 108

mSceneMgr->getSceneNode("carnode")->setScale(Ogre::Vector3(0.5,0.5,0.5));
mSceneMgr->getSceneNode("carnode")->setOrientation(-0.5,-0.5,0.5,-0.5);
mSceneMgr->getSceneNode("carnode")->setPosition(Ogre::Vector3(0,30,0));

chassisShape = new btBoxShape(btVector3(vrre.y*0.5,vrre.z*0.5,vrre.x*0.5) );
compound = new btCompoundShape();

localTrans.setIdentity();
localTrans.setOrigin(btVector3(0,30,0));
compound->addChildShape(localTrans,chassisShape);

chassisShape->calculateLocalInertia(800,localInertia);
motionstate = new CarMotionState(btTransform(btQuaternion( 0,0,0,1),btVector3(btScalar(0),btScalar(0),btScalar(0))),node);
btRigidBody::btRigidBodyConstructionInfo cInfo(800,motionstate,compound,localInertia);
body = new btRigidBody(cInfo);
static_cast <btDynamicsWorld *> (mWorld)->addRigidBody (body);
body->setRestitution(0.6);
body->setFriction(0.6);
body->setDamping(0.2,0.2);
mWorld->getBroadphase()->getOverlappingPairCache()->cleanProxyFromPairs(body->getBroadphaseHandle(),mWorld->getDispatcher());

m_vehicleRayCaster = new btDefaultVehicleRaycaster(static_cast <btDynamicsWorld *> (mWorld));
m_vehicle = new btRaycastVehicle(mTuning,body,m_vehicleRayCaster);
body->setActivationState(DISABLE_DEACTIVATION);
static_cast <btDynamicsWorld *> (mWorld)->addVehicle(m_vehicle);

int rightIndex = 0;
int upIndex = 1;
int forwardIndex = 2;
m_vehicle->setCoordinateSystem(rightIndex, upIndex, forwardIndex);//X，Y，Z

Ogre::SceneNode* tmpnode;
for (size_t i = 0; i < 4; i++)
{
mWheels[i] = mSceneMgr->createEntity(
"wheel" + StringConverter::toString(i),
"Entity91.mesh");
mWheels[i]->setCastShadows(true);
mWheelNodes[i] = mSceneMgr->getRootSceneNode ()->createChildSceneNode ();
tmpnode=mWheelNodes[i]->createChildSceneNode();

tmpnode->attachObject (mWheels[i]);
tmpnode->setScale(Ogre::Vector3(0.5,0.5,0.5));
tmpnode->setOrientation(-0.5,-0.5,0.5,-0.5);

}



motionstate->setVehicle(m_vehicle);
motionstate->setVehicleRaycaster(m_vehicleRayCaster);
motionstate->setVehicleTuning(mTuning);
motionstate->setWheelNode(mWheelNodes);




//wheel1
isFrontWheel=true;
btVector3 connectionPointCS0;

connectionPointCS0=btVector3(178-(0.3*wheelWidth),connectionHeight,419-wheelRadius);
connectionPointCS0=connectionPointCS0*0.4;
m_vehicle->addWheel(connectionPointCS0,wheelDirectionCS0,wheelAxleCS,suspensionRestLength,wheelRadius,mTuning,isFrontWheel);


//wheel2
connectionPointCS0 = btVector3(-178+(0.3*wheelWidth),connectionHeight,419-wheelRadius);
connectionPointCS0=connectionPointCS0*0.4;
m_vehicle->addWheel(connectionPointCS0,wheelDirectionCS0,wheelAxleCS,suspensionRestLength,wheelRadius,mTuning,isFrontWheel);

//wheel3
isFrontWheel = false;
connectionPointCS0 = btVector3(-178+(0.3*wheelWidth),connectionHeight,-419+wheelRadius);
connectionPointCS0=connectionPointCS0*0.4;
m_vehicle->addWheel(connectionPointCS0,wheelDirectionCS0,wheelAxleCS,suspensionRestLength,wheelRadius,mTuning,isFrontWheel);

//wheel4
connectionPointCS0 = btVector3(178-(0.3*wheelWidth),connectionHeight,-419+wheelRadius);
connectionPointCS0=connectionPointCS0*0.4;

m_vehicle->addWheel(connectionPointCS0,wheelDirectionCS0,wheelAxleCS,suspensionRestLength,wheelRadius,mTuning,isFrontWheel);
motionstate->setWheelsAttached();

m_vehicle->applyEngineForce(30000.0, 0);
m_vehicle->applyEngineForce(30000.0, 0);
m_vehicle->setSteeringValue(0.6,0);
m_vehicle->setSteeringValue(0.6,1);
body->setLinearVelocity ( btVector3(0,300,0));

}
*/