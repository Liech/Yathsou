#pragma once

#include <memory>
#include <functional>

namespace Iyathuum {
  class State;

  class StateTransition {
  public:
    StateTransition(std::shared_ptr<State> from, std::shared_ptr<State> to, std::function<bool()> condition);

    void addTransitionEvent(std::function<void()>);
    void callTransitionEvents();
    bool conditionIsFullfilled() const;

    std::shared_ptr<State> stateFrom() const;
    std::shared_ptr<State> stateTo()   const;

  private:
    std::shared_ptr<State>             _from;
    std::shared_ptr<State>             _to;    
    std::function<bool()>              _condition;
    std::vector<std::function<void()>> _transitionEvents;
  };
}