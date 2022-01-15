#pragma once

#include "IyathuumCoreLib/lib/glm/glm.hpp"

class btRigidBody;

namespace Suthanus {
  class BulletCore {
  public:
    BulletCore(btRigidBody* body);

    glm::quat getRotation()       const;
    glm::vec3 getPosition()       const;
    glm::mat4 getTransformation() const;

    void setPosition       (const glm::vec3& pos);
    void setRotation       (const glm::quat& rot);
    void setAngularVelocity(const glm::vec3& pos);
    void setVelocity       (const glm::vec3& pos);
    void addForce          (const glm::vec3& force, const glm::vec3& offset);

  private:
    btRigidBody* _body;
  };
}