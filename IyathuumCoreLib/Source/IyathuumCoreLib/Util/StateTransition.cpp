#include "StateTransition.h"

namespace Iyathuum {
  StateTransition::StateTransition(std::shared_ptr<State> from, std::shared_ptr<State> to, std::function<bool()> condition) {
    _from      = from;
    _to        = to;
    _condition = condition;
  }

  bool StateTransition::conditionIsFullfilled() const {
    return _condition();
  }

  void StateTransition::addTransitionEvent(std::function<void()> event) {
    _transitionEvents.push_back(event);
  }

  void StateTransition::callTransitionEvents() {
    for (auto& x : _transitionEvents)
      x();
  }

  std::shared_ptr<State> StateTransition::stateFrom() const {
    return _from;
  }
  
  std::shared_ptr<State> StateTransition::stateTo()   const {
    return _to;
  }
}