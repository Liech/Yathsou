#pragma once

#include <map>
#include <string>
#include <memory>
#include <vector>

namespace Iyathuum {
  class State;
  class StateTransition;

  class StateMachine {
  public:
    StateMachine(std::shared_ptr<State> startState);
    virtual ~StateMachine() = default;

    void addState(std::shared_ptr<State>);
    std::shared_ptr<State> currentState();

    void addTransition(std::shared_ptr<StateTransition> transition);

    void update();    

  private:
    std::map<std::string, std::vector<std::shared_ptr<StateTransition>>> _transitions;
    std::map<std::string, std::shared_ptr<State>>                        _states;
    std::shared_ptr<State>                                               _currentState;
  };
}