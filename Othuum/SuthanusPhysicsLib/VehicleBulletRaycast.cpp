#include "VehicleBulletRaycast.h"

#include "lib/bullet/btBulletDynamicsCommon.h"
#include "IyathuumCoreLib/lib/glm/gtc/type_ptr.hpp"

namespace Suthanus
{
  namespace Bullet
  {
    VehicleBulletRaycast::VehicleBulletRaycast(btDiscreteDynamicsWorld* world, glm::vec3 pos)
    {
      _world = world;
      btCollisionShape* colShape = new btBoxShape(btVector3(getSize()[0], getSize()[1], getSize()[2]));
      //btCollisionShape* colShape = new btSphereShape(btScalar(1.));

      /// Create Dynamic Objects
      btTransform startTransform;
      startTransform.setIdentity();

      btScalar mass(1.f);
      btVector3 localInertia(0, 0, 0);
      colShape->calculateLocalInertia(mass, localInertia);

      startTransform.setOrigin(btVector3(pos[0], pos[1], pos[2]));
      btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
      btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);

      _body = new btRigidBody(rbInfo);
      _world->addRigidBody(_body);
    }

    glm::vec3 VehicleBulletRaycast::getPosition()
    {
      auto trans = _body->getWorldTransform().getOrigin();
      return glm::vec3(trans[0], trans[1], trans[2]);
    }

    glm::mat4 VehicleBulletRaycast::getTransformation()
    {
      glm::mat4 result;
      btTransform trans = _body->getWorldTransform();
      float mat[16];
      trans.getOpenGLMatrix(mat);
      return glm::make_mat4(mat);
    }

    glm::vec3 VehicleBulletRaycast::getSize()
    {
      return glm::vec3(0.8, 0.4, 0.4);
    }
  }
}