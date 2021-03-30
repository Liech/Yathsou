#pragma once

#include <functional>
#include <memory>
#include "YolonaOss/OpenGL/Updateable.h"
#include "VishalaNetworkLib/Core/Command.h"

namespace Uyanah {
  class Scene;
  namespace Commands {
    class Command;
  } 
}

class ClientControl : public YolonaOss::GL::Updateable {
public:
  ClientControl() = default;
  ClientControl(std::function<void(std::shared_ptr<Vishala::ICommand>)> sendCommand,
                std::shared_ptr<const Uyanah::Scene> scene);
  void update();
  virtual void load(YolonaOss::GL::DrawSpecification*) override;
private:
  bool _w = false;
  bool _a = false;
  bool _s = false;
  bool _d = false;

  YolonaOss::GL::Window*                                _window     ;
  std::shared_ptr<const Uyanah::Scene>                  _scene      ;
  std::function<void(std::shared_ptr<Vishala::ICommand>)> _sendCommand;

};