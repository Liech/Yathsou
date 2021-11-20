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

    void setPosition(glm::vec3 pos);
    void setRotation(glm::quat rot);
    void setAngularVelocity(glm::vec3 pos);
    void setVelocity(glm::vec3 pos);

  private:
    btRigidBody* _body;
  };
}