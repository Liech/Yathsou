#include "SphereReact.h"

#include <reactphysics3d/reactphysics3d.h>

#include "SuthanusPhysicsLib/PhysicEngineReact.h"

namespace Suthanus
{
  namespace React {
    SphereReact::SphereReact(PhysicEngineReact& engine, const glm::vec3& pos, float radius, bool isDynamic) : _physic(engine){
      _shape = _physic.common().createSphereShape(radius);
      _body  = _physic.world().createRigidBody(transform);
      Collider* collider;
      collider = body->addCollider(&shape, transform);

    }

    SphereReact::~SphereReact() {
      _physic.world().destroyRigidBody(_body);
    }

    glm::vec3 SphereReact::getPosition() const {
      return glm::vec3(0);
    }

    glm::mat4 SphereReact::getTransformation() const {
      return glm::mat4(1);
    }

    glm::quat SphereReact::getRotation() const {
      return glm::quat();
    }

    void SphereReact::setVelocity(glm::vec3) {

    }

    void SphereReact::setPosition(glm::vec3) {

    }

    void SphereReact::setAngularVelocity(glm::vec3) {

    }

    void SphereReact::setRotation(glm::quat) {

    }

    float SphereReact::getRadius() const {
      return 1;
    }
  }
}