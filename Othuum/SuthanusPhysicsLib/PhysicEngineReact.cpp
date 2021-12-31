#include "PhysicEngineReact.h"

#include <reactphysics3d/reactphysics3d.h>

namespace Suthanus {
  PhysicEngineReact::PhysicEngineReact() {
    reactphysics3d::PhysicsCommon physicsCommon;
    reactphysics3d::PhysicsWorld* world = physicsCommon.createPhysicsWorld();
    reactphysics3d::SphereShape* sphereShape = physicsCommon.createSphereShape(2.0);
  }
}