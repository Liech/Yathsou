#pragma once

#include "UnitAgentInterface.h"

namespace Superb {
  class Unit;

  class WheeledSteeringAgent : public UnitAgentInterface {
  public:
    typedef Selen::AgentMovementInterface<3>::vec v3;

    WheeledSteeringAgent();
    virtual ~WheeledSteeringAgent() = default;

    virtual void setTarget(Unit*) override;
    virtual void update()         override;

    glm::vec3 getDesiredDirection();
    float     getDesiredSpeed();

    virtual void  setDesiredDirection(const v3&)       override;
    virtual void  setDesiredSpeed(float)               override;
    virtual v3    getDirection()                 const override;
    virtual v3    getPosition ()                 const override;
    virtual float getMaximumSpeed()              const override;
    virtual float getBreakSpeed()                const override;
    virtual float getRadius()                    const override;
  private:
    Unit* _target = nullptr;    

    glm::vec3 _desiredDirection = glm::vec3(0);
    float     _desiredSpeed     = 0;
  };
}