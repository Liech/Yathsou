#include "StateMachine.h"

#include <stdexcept>
#include <iostream>

#include "State.h"
#include "StateTransition.h"

namespace Iyathuum {
  StateMachine::StateMachine(std::shared_ptr<State> startState) {
    _currentState = startState;
    addState(startState);
  }
  
  void StateMachine::update() {
    bool workDone = false;
    do {
      workDone = false;
      for (auto& x : _transitions[currentState()->name()]) {
        if (x->conditionIsFullfilled()) {
          workDone = true;
          //std::cout << "State Transition from: \"" << currentState()->name() << "\" to \"" << x->stateTo()->name() << "\"" << std::endl;
          _currentState->leave();
          _currentState = x->stateTo();
          _currentState->enter();
          x->callTransitionEvents();          
          break;
        }
      }
    } while (workDone);
  }

  std::shared_ptr<State> StateMachine::currentState() {
    return _currentState;
  }

  void StateMachine::addTransition(std::shared_ptr<StateTransition> transition) {
    std::string fromName = transition->stateFrom()->name();
    if (_states.count(fromName) == 0)
      throw std::runtime_error("State Transition Origin not in StateMachine");
    if (_states.count(transition->stateTo()->name()) == 0)
      throw std::runtime_error("State Transition Target not in StateMachine");
    _transitions[fromName].push_back(transition);
  }

  void StateMachine::addState(std::shared_ptr<State> state) {
    if (!state)
      throw std::runtime_error("State must not be null");
    if (_states.count(state->name()) != 0)
      throw std::runtime_error("There is already a state with the given name");
    _states[state->name()] = state;
    _transitions[state->name()] = {};
  }
}