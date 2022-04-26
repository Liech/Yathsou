#include "State.h"

namespace Iyathuum {
  State::State(const std::string& name, void* userData) {
    _userData = userData;
    _name     = name;
  }

  std::string State::name() const {
    return _name;
  }

  void State::setOnLeaveCallback(std::function<void()> callback) {
    _onLeave = callback;
  }

  void State::setOnEnterCallback(std::function<void()> callback) {
    _onEnter = callback;
  }

  void State::leave() {
    _onLeave();
  }

  void State::enter() {
    _onEnter();
  }
}