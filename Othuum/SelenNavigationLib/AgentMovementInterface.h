#pragma once

#include "IyathuumCoreLib/lib/glm/glm.hpp"

namespace Selen {
  template <size_t Dimension>
  class AgentMovementInterface {
  public:
    using vec = glm::vec<Dimension, float, glm::defaultp>;

    virtual ~AgentMovementInterface() = default;

    virtual void  setDesiredDirection (const vec&) = 0;
    virtual void  setDesiredSpeed     (float)      = 0;

    virtual vec   getCurrentDirection () const     = 0;
    virtual float getMaximumSpeed     () const     = 0;
    virtual float getBreakSpeed       () const     = 0;
  private:
  };
}