#pragma once

#include <glm/glm.hpp>

namespace Selen {
  template <size_t Dimension>
  class AgentMovementInterface {
  public:
    using vec = glm::vec<Dimension, float, glm::defaultp>;

    virtual ~AgentMovementInterface() = default;

    virtual void  setDesiredDirection (const vec&) = 0;
    virtual void  setDesiredSpeed     (float)      = 0;

    virtual vec   getPosition         () const     = 0;
    virtual vec   getDirection        () const     = 0;
    virtual float getMaximumSpeed     () const     = 0;
    virtual float getBreakSpeed       () const     = 0;
    virtual std::array<float,Dimension> getSize() const     = 0;
  private:
  };
}