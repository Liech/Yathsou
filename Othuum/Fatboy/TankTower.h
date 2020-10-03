#pragma once

#include <memory>

#include "YolonaOss/OpenGL/Drawable.h"
#include "YolonaOss/OpenGL/Updateable.h"
#include "IyathuumCoreLib/lib/glm/vec3.hpp"
#include "SuthanusPhysicsLib/PhysicObject.h"
#include "IyathuumCoreLib/lib/glm/gtx/quaternion.hpp"

namespace Fatboy
{
  class TankTower : public YolonaOss::GL::Drawable, public YolonaOss::GL::Updateable
  {
  public:
    TankTower(Suthanus::PhysicObject& attachTo, glm::vec3 offset, glm::vec3 startDirection);

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

    virtual void load(YolonaOss::GL::DrawSpecification*) override;
    virtual void draw()                                  override;
    virtual void update()                                override;
  private:
    void rotateTowardsTargetDir();
    void updateYRotationTarget();

    float getTurnRadianPerTick();

    float                   _maxAimUp       = 40;
    float                   _maxAimDown     = 90;
    float                   _turnSpeed      = 90;
    glm::vec3               _targetDirection;

    glm::quat               _direction ;
    glm::vec3               _offset    ;
    Suthanus::PhysicObject& _attachedTo;
  };
}