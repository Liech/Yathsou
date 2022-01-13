#include "SphereBullet.h"

#include "SuthanusPhysicsLib/lib/bullet/btBulletDynamicsCommon.h"
#include "IyathuumCoreLib/lib/glm/gtc/type_ptr.hpp"
#include "SuthanusPhysicsLib/Objects/BulletCore.h"

namespace Suthanus
{
  namespace Bullet
  {
    SphereBullet::SphereBullet(PhysicEngine& engine, btDiscreteDynamicsWorld* world, glm::vec3 pos, float radius, bool isDynamic) : Sphere(engine)
    {
      _world = world;
      _radius = radius;
      btCollisionShape* colShape = new btSphereShape(radius);

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
      //_body->setCcdMotionThreshold(1e-7)  ;
      //_body->setCcdSweptSphereRadius(radius);
      _body->setUserPointer(this);
      _world->addRigidBody(_body);
      _body->setCollisionFlags(_body->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
      _core = std::make_unique<BulletCore>(_body);
    }

    SphereBullet::~SphereBullet()
    {
      _world->removeRigidBody(_body);
      delete _motionState;
      delete _body;
    }

    glm::vec3 SphereBullet::getPosition() const
    {
      return _core->getPosition();
    }

    glm::mat4 SphereBullet::getTransformation() const
    {
      return _core->getTransformation();
    }

    float SphereBullet::getRadius() const
    {
      return _radius;
    }

    void SphereBullet::setPosition(glm::vec3 pos) {
      _core->setPosition(pos);
    }

    void SphereBullet::setVelocity(glm::vec3 pos) {
      _core->setVelocity(pos);
    }

    void SphereBullet::setAngularVelocity(glm::vec3 rot) {
      _core->setAngularVelocity(rot);
    }

    glm::quat SphereBullet::getRotation() const
    {
      return _core->getRotation();
    }

    void SphereBullet::setRotation(glm::quat rot) {
      _core->setRotation(rot);
    }
  }
}