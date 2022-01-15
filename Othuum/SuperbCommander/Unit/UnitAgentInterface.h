#pragma once

#include "SelenNavigationLib/AgentMovementInterface.h"

namespace Superb {
  class Unit;

  class UnitAgentInterface : public Selen::AgentMovementInterface<3> {
  public:
    virtual ~UnitAgentInterface() = default;

    virtual void update()         = 0;    
    virtual void setTarget(Unit*) = 0;
    virtual void debugDraw()      = 0;

  };
}