#pragma once

#include <string>
#include <functional>

namespace Iyathuum {
  class State {
  public:
    State(const std::string& name, void* userData = nullptr);

    std::string name() const;

    void setOnLeaveCallback(std::function<void()>);
    void setOnEnterCallback(std::function<void()>);

    void leave();
    void enter();

    template<typename T>
    T data() {
      return (T)_userData;
    }
  private:
    std::string _name;
    void*       _userData;
    
    std::function<void()> _onLeave = [](){};
    std::function<void()> _onEnter = [](){};
  };
}