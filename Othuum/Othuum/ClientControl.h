#pragma once

#include <functional>
#include <memory>
#include "YolonaOss/OpenGL/Updateable.h"
#include "UyanahGameServer/Commands/Command.h"

namespace Uyanah {
  class Scene;
  namespace Commands {
    class Command;
  } 
}

class ClientControl : public YolonaOss::GL::Updateable {
public:
  ClientControl() = default;
  ClientControl(std::function<void(std::shared_ptr<Uyanah::Commands::Command>)> sendCommand,
                std::shared_ptr<const Uyanah::Scene> scene);
  void update();
  virtual void load(YolonaOss::GL::DrawSpecification*) override;
private:
  YolonaOss::GL::Window*                                _window     ;
  std::shared_ptr<const Uyanah::Scene>                  _scene      ;
  std::function<void(std::shared_ptr<Uyanah::Commands::Command>)> _sendCommand;

};