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
    virtual void debugDraw()      override; 
    virtual void update()         override;

    virtual void  setDesiredDirection(const v3&)       override;
    virtual void  setDesiredSpeed(float)               override;
    virtual v3   getCurrentDirection()           const override;
    virtual float getMaximumSpeed()              const override;
    virtual float getBreakSpeed()                const override;
  private:
    Unit* _target;    
  };
}