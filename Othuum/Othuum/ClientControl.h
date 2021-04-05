#pragma once

#include <functional>
#include <memory>
#include "AhwassaGraphicsLib/Core/Window.h"
#include "VishalaNetworkLib/Core/Command.h"

namespace Uyanah {
  class Scene;
  namespace Commands {
    class Command;
  } 
}

class ClientControl {
public:
  ClientControl(Ahwassa::Window*);
  ClientControl(std::function<void(std::shared_ptr<Vishala::ICommand>)> sendCommand,
                std::shared_ptr<const Uyanah::Scene> scene, Ahwassa::Window*);
  void update();
private:
  bool _w = false;
  bool _a = false;
  bool _s = false;
  bool _d = false;

  Ahwassa::Window*                                        _window     ;
  std::shared_ptr<const Uyanah::Scene>                    _scene      ;
  std::function<void(std::shared_ptr<Vishala::ICommand>)> _sendCommand;

};