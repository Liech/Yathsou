#include "BoxBullet.h"

#include <stdexcept>
#include "SuthanusPhysicsLib/lib/bullet/btBulletDynamicsCommon.h"
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
      _motionState = new btDefaultMotionState(startTransform);
      btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, _motionState, colShape, localInertia);

      _body = new btRigidBody(rbInfo);
      _body->setUserPointer(this);
      _world->addRigidBody(_body);
      _body->setCollisionFlags(_body->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
    }

    BoxBullet::~BoxBullet()
    {
    }

    void BoxBullet::dispose()
    {
      _world->removeRigidBody(_body);
      delete _motionState;
      delete _body;
    }


    glm::vec3 BoxBullet::getPosition() const
    {
      auto trans = _body->getWorldTransform().getOrigin();
      return glm::vec3(trans[0], trans[1], trans[2]);
    }

    glm::mat4 BoxBullet::getTransformation() const
    {
      glm::mat4 result;
      btTransform trans = _body->getWorldTransform();
      double mat[16];
      trans.getOpenGLMatrix(mat);
      return glm::make_mat4(mat);
    }

    glm::vec3 BoxBullet::getSize()
    {
      return _size;
    }

    void BoxBullet::setPosition(glm::vec3 pos) {
      btTransform transform = _body->getCenterOfMassTransform();
      transform.setOrigin(btVector3(pos[0], pos[1], pos[2]));
      _body->setCenterOfMassTransform(transform);
    }

    void BoxBullet::setVelocity(glm::vec3 pos) {
      _body->setLinearVelocity(btVector3(pos[0],pos[1],pos[2]));
    }

    void BoxBullet::setAngularVelocity(glm::vec3 velocity)
    {
      _body->setAngularVelocity(btVector3(velocity[0], velocity[1], velocity[2]));
    }

    glm::quat BoxBullet::getRotation() const
    {
      btTransform transform = _body->getCenterOfMassTransform();
      auto rot = transform.getRotation();
      return glm::quat(rot.x(), rot.y(), rot.z(), rot.w());
    }

    void BoxBullet::setRotation(glm::quat rot) {
      btTransform transform = _body->getCenterOfMassTransform();
      btQuaternion q;
      q.setX(rot.x);
      q.setY(rot.y);
      q.setZ(rot.z);
      q.setW(rot.w);
      transform.setRotation(btQuaternion());
      _body->setCenterOfMassTransform(transform);
    }
  }
}