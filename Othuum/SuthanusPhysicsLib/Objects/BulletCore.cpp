#include "BulletCore.h"

#include "SuthanusPhysicsLib/lib/bullet/btBulletDynamicsCommon.h"
#include "IyathuumCoreLib/lib/glm/gtc/type_ptr.hpp"

namespace Suthanus {
  BulletCore::BulletCore(btRigidBody* body) {
    _body = body;
  }

  glm::vec3 BulletCore::getPosition() const
  {
    auto trans = _body->getWorldTransform().getOrigin();
    return glm::vec3(trans[0], trans[1], trans[2]);
  }

  void BulletCore::setPosition(glm::vec3 pos) {
    btTransform transform = _body->getCenterOfMassTransform();
    transform.setOrigin(btVector3(pos[0], pos[1], pos[2]));
    _body->setCenterOfMassTransform(transform);
  }

  glm::mat4 BulletCore::getTransformation() const
  {
    glm::mat4 result;
    btTransform trans = _body->getWorldTransform();
    float mat[16];
    trans.getOpenGLMatrix(mat);
    return glm::make_mat4(mat);
  }

  glm::quat BulletCore::getRotation() const
  {
    btTransform transform = _body->getCenterOfMassTransform();
    auto rot = transform.getRotation();
    return glm::quat(rot.x(), rot.y(), rot.z(), rot.w());
  }

  void BulletCore::setRotation(glm::quat rot) {
    btTransform transform = _body->getCenterOfMassTransform();
    btQuaternion q;
    q.setX(rot.x);
    q.setY(rot.y);
    q.setZ(rot.z);
    q.setW(rot.w);
    transform.setRotation(q);
    _body->setCenterOfMassTransform(transform);
  }

  void BulletCore::setAngularVelocity(glm::vec3 rot) {
    _body->setAngularVelocity(btVector3(rot[0], rot[1], rot[2]));
  }

  void BulletCore::setVelocity(glm::vec3 pos) {
    _body->setLinearVelocity(btVector3(pos[0], pos[1], pos[2]));
  }



}