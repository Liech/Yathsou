#include "BoxBullet.h"

#include "lib/bullet/btBulletDynamicsCommon.h"
#include "IyathuumCoreLib/lib/glm/gtc/type_ptr.hpp"
namespace Suthanus
{
  namespace Bullet
  {
    BoxBullet::BoxBullet(btDiscreteDynamicsWorld* world, glm::vec3 pos, glm::vec3 size, bool isDynamic)
    {
      _world = world;
      _size = size;
      btCollisionShape* colShape = new btBoxShape(btVector3(size[0] / 2, size[1] / 2, size[2] / 2));
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

    glm::vec3 BoxBullet::getPosition()
    {
      auto trans = _body->getWorldTransform().getOrigin();
      return glm::vec3(trans[0], trans[1], trans[2]);
    }

    glm::mat4 BoxBullet::getTransformation()
    {
      glm::mat4 result;
      btTransform trans = _body->getWorldTransform();
      float mat[16];
      trans.getOpenGLMatrix(mat);
      return glm::make_mat4(mat);
    }

    glm::vec3 BoxBullet::getSize()
    {
      return _size;
    }
  }
}