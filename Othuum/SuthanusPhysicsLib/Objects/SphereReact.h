#pragma once

#include "Sphere.h"

namespace reactphysics3d {
  class PhysicsCommon;
  class SphereShape;
}

namespace Suthanus
{
  class PhysicEngineReact;

  namespace React {
    class SphereReact : public Sphere
    {
    public:
      SphereReact(PhysicEngineReact& common, const glm::vec3& pos, float radius, bool isDynamic);
      ~SphereReact();

      virtual glm::vec3 getPosition()           const override;
      virtual glm::mat4 getTransformation()     const override;
      virtual glm::quat getRotation()           const override;
      virtual void      setVelocity(glm::vec3)        override;
      virtual void      setPosition(glm::vec3)        override;
      virtual void      setAngularVelocity(glm::vec3) override;
      virtual void      setRotation(glm::quat)        override;
      virtual float     getRadius()             const override;

    private:
      PhysicEngineReact& _physic;

      reactphysics3d::SphereShape* _shape;
      reactphysics3d::RigidBody*   _body ;
    };
  }
}