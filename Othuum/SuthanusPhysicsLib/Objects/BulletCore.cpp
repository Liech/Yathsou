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

  void BulletCore::setPosition(const glm::vec3& pos) {
    btTransform transform = _body->getCenterOfMassTransform();
    transform.setOrigin(btVector3(pos[0], pos[1], pos[2]));
    _body->setCenterOfMassTransform(transform);
  }

  glm::mat4 BulletCore::getTransformation() const
  {
    glm::mat4 result;
    btTransform trans = _body->getWorldTransform();
    double mat[16];
    trans.getOpenGLMatrix(mat);
    return glm::make_mat4(mat);
  }

  glm::quat BulletCore::getRotation() const
  {
    btTransform transform = _body->getCenterOfMassTransform();
    auto rot = transform.getRotation();
    return glm::quat(rot.w(), rot.x(), rot.y(), rot.z());
  }

  void BulletCore::setRotation(const glm::quat& rot) {
    btTransform transform = _body->getCenterOfMassTransform();
    btQuaternion q;
    q.setX(rot.x);
    q.setY(rot.y);
    q.setZ(rot.z);
    q.setW(rot.w);
    transform.setRotation(q);
    _body->setCenterOfMassTransform(transform);
  }

  void BulletCore::setAngularVelocity(const glm::vec3& rot) {
    _body->setAngularVelocity(btVector3(rot[0], rot[1], rot[2]));
  }

  void BulletCore::setVelocity(const glm::vec3& pos) {
    _body->setLinearVelocity(btVector3(pos[0], pos[1], pos[2]));
  }

  void BulletCore::addForce(const glm::vec3& force, const glm::vec3& offset) {
    
    _body->applyForce(btVector3(force[0],force[1],force[2]), _body->getCenterOfMassTransform().getOrigin() + btVector3(offset[0],offset[1],offset[2]));
  }


}