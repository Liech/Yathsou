#include "BoxBullet.h"

#include <bullet/btBulletDynamicsCommon.h>
#include <glm/gtc/type_ptr.hpp>
#include "BulletCore.h"

namespace Suthanus
{
  namespace Bullet
  {
    BoxBullet::BoxBullet(PhysicEngine& engine, btDiscreteDynamicsWorld* world, glm::vec3 pos, glm::vec3 size, bool isDynamic) : Box(engine)
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

      _core = std::make_unique<BulletCore>(_body);
    }

    BoxBullet::~BoxBullet()
    {
      _world->removeRigidBody(_body);
      delete _motionState;
      delete _body;
    }

    glm::vec3 BoxBullet::getPosition() const
    {
      return _core->getPosition();
    }

    glm::mat4 BoxBullet::getTransformation() const
    {
      return _core->getTransformation();
    }

    glm::vec3 BoxBullet::getSize()
    {
      return _size;
    }

    void BoxBullet::setPosition(const glm::vec3& pos) {
      _core->setPosition(pos);
    }

    void BoxBullet::setVelocity(const glm::vec3& pos) {
      _core->setVelocity(pos);
    }

    void BoxBullet::setAngularVelocity(const glm::vec3& velocity)
    {
      _core->setVelocity(velocity);
    }

    glm::quat BoxBullet::getRotation() const
    {
      return _core->getRotation();
    }

    void BoxBullet::setRotation(const glm::quat& rot) {
      _core->setRotation(rot);
    }

    void BoxBullet::addForce(const glm::vec3& force, const glm::vec3& offset) {
      _core->addForce(force, offset);
    }
  }
}