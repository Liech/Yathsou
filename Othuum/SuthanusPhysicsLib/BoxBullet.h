#pragma once

#include "Box.h"

class btRigidBody;
namespace Suthanus
{
  class BoxBullet : public Box
  {
  public:
    BoxBullet(btRigidBody* body);
    virtual glm::vec3 getPosition() override;


  private:

    btRigidBody* _body;
  };
}