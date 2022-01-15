#pragma once

#include "IyathuumCoreLib/lib/glm/glm.hpp"
#include "IyathuumCoreLib/BaseTypes/Command.h"
#include "AgentMovementInterface.h"

namespace Selen {
  template<size_t Dimension>
  class DirectTargetMovement : public Iyathuum::Command{
  public:
    using vec = glm::vec<Dimension, float, glm::defaultp>;

    DirectTargetMovement(AgentMovementInterface<Dimension>& agent, float fullfillmentDistance = 1) : _agent(agent) {
      _fullfillmentDistance = fullfillmentDistance;
    }

    virtual ~DirectTargetMovement() = default;

    virtual bool isFullfilled() override {
      float distance = glm::distance(_target, _agent->getPosition());
      return distance < _fullfillmentDistance;
    }

    virtual void update() override {
      vec   diff = _target - _agent->getPosition();
      _agent->setDesiredDirection(glm::normalize(diff));
      _agent->setDesiredSpeed(_agent->getMaximumSpeed());
    }

    void setTarget(const vec& target) {
      _target = target;
    }

    virtual void cleanup() override{
      _agent->setDesiredSpeed(0);
      _agent->setDesiredDirection(vec(0));
    }

  private:
    float                              _fullfillmentDistance = 1;
    AgentMovementInterface<Dimension>& _agent ;
    vec                                _target;
  };
}