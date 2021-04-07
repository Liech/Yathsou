#pragma once

#include <memory>

#include "AhwassaGraphicsLib/Drawables/Drawable.h"
#include "IyathuumCoreLib/lib/glm/vec3.hpp"
#include "SuthanusPhysicsLib/PhysicObject.h"
#include "IyathuumCoreLib/lib/glm/gtx/quaternion.hpp"

namespace Ahwassa {
  class BasicBoxRenderer;
}

namespace Fatboy
{
  class TankTower : public Ahwassa::Drawable
  {
  public:
    TankTower(Suthanus::PhysicObject& attachTo, glm::vec3 offset, glm::vec3 startDirection, Ahwassa::Window* w);

    float getMaxAimUp  ();
    float getMaxAimDown();
    float getTurnSpeed ();
    glm::vec3 getTargetDirection();
    glm::vec3 getGlobalTargetDirection();
    glm::vec3 getCurrentDirection();
    glm::vec3 getCurrentGlobalDirection();
    glm::vec3 getGlobalPosition();

    void setMaxAimUp  (float maxDegree);
    void setMaxAimDown(float maxDegree);
    void setTurnSpeed (float degreePerSecond);
    void setGlobalTargetDirection(glm::vec3 dir);    

    virtual void draw()                                  override;
    void update();
  private:
    void rotateTowardsTargetDir();
    void updateYRotationTarget();

    float getTurnRadianPerTick();

    float                   _maxAimUp       = 40;
    float                   _maxAimDown     = 80;
    float                   _turnSpeed      = 90;
    glm::vec3               _targetDirection;

    glm::quat               _direction ;
    glm::vec3               _offset    ;
    Suthanus::PhysicObject& _attachedTo;

    std::shared_ptr<Ahwassa::BasicBoxRenderer> _box;
  };
}