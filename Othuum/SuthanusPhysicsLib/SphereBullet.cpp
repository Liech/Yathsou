#include "SphereBullet.h"

#include "lib/bullet/btBulletDynamicsCommon.h"
#include "IyathuumCoreLib/lib/glm/gtc/type_ptr.hpp"
namespace Suthanus
{
  namespace Bullet
  {
    SphereBullet::SphereBullet(btDiscreteDynamicsWorld* world, glm::vec3 pos, float radius, bool isDynamic)
    {
      _world = world;
      _radius = radius;
      btCollisionShape* colShape = new btSphereShape(radius);
      //btCollisionShape* colShape = new btSphereShape(btScalar(1.));

      /// Create Dynamic Objects
      btTransform startTransform;
      startTransform.setIdentity();

      btScalar mass(1.f);
      if (!isDynamic)
        mass = 0;
      btVector3 localInertia(0, 0, 0);
      if (isDynamic)
        colShape->calculateLocalInertia(mass, localInertia);

      startTransform.setOrigin(btVector3(pos[0], pos[1], pos[2]));
      btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
      btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);

      _body = new btRigidBody(rbInfo);
      _world->addRigidBody(_body);
    }

    glm::vec3 SphereBullet::getPosition() const
    {
      auto trans = _body->getWorldTransform().getOrigin();
      return glm::vec3(trans[0], trans[1], trans[2]);
    }

    glm::mat4 SphereBullet::getTransformation() const
    {
      glm::mat4 result;
      btTransform trans = _body->getWorldTransform();
      float mat[16];
      trans.getOpenGLMatrix(mat);
      return glm::make_mat4(mat);
    }

    float SphereBullet::getRadius()
    {
      return _radius;
    }
  }
}