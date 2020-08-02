#include "BoxBullet.h"

#include "lib/bullet/btBulletDynamicsCommon.h"

namespace Suthanus
{
  BoxBullet::BoxBullet(btRigidBody* body)
  {
    _body = body;
  }

  glm::vec3 BoxBullet::getPosition()
  {
    auto trans = _body->getWorldTransform().getOrigin();
    return glm::vec3(trans[0], trans[1], trans[2]);
  }

}