#include "ClientControl.h"

#include "YolonaOss/OpenGL/Window.h"
#include "UyanahGameServer/Commands/Key.h"

ClientControl::ClientControl(std::function<void(std::shared_ptr<Uyanah::Commands::Command>)> sendCommand,
  std::shared_ptr<const Uyanah::Scene> scene) {
  _scene = scene;
  _sendCommand = sendCommand;
}

void ClientControl::update() {
  bool w = _window->getKeyStatus(Iyathuum::Key::KEY_W) == Iyathuum::KeyStatus::PRESS;
  bool a = _window->getKeyStatus(Iyathuum::Key::KEY_A) == Iyathuum::KeyStatus::PRESS;
  bool s = _window->getKeyStatus(Iyathuum::Key::KEY_S) == Iyathuum::KeyStatus::PRESS;
  bool d = _window->getKeyStatus(Iyathuum::Key::KEY_D) == Iyathuum::KeyStatus::PRESS;

  if (w)
  {
    auto wCmd = std::make_shared<Uyanah::Commands::KeyCmd>();
    wCmd->key = Iyathuum::Key::KEY_W;
    std::shared_ptr<Uyanah::Commands::Command> cast = std::static_pointer_cast<Uyanah::Commands::KeyCmd>(wCmd);
    _sendCommand(cast);
  }
  if (a)
  {
    auto wCmd = std::make_shared<Uyanah::Commands::KeyCmd>();
    wCmd->key = Iyathuum::Key::KEY_A;
    std::shared_ptr<Uyanah::Commands::Command> cast = std::static_pointer_cast<Uyanah::Commands::KeyCmd>(wCmd);
    _sendCommand(cast);
  }
  if (s)
  {
    auto wCmd = std::make_shared<Uyanah::Commands::KeyCmd>();
    wCmd->key = Iyathuum::Key::KEY_S;
    std::shared_ptr<Uyanah::Commands::Command> cast = std::static_pointer_cast<Uyanah::Commands::KeyCmd>(wCmd);
    _sendCommand(cast);
  }
  if (d)
  {
    auto wCmd = std::make_shared<Uyanah::Commands::KeyCmd>();
    wCmd->key = Iyathuum::Key::KEY_D;
    std::shared_ptr<Uyanah::Commands::Command> cast = std::static_pointer_cast<Uyanah::Commands::KeyCmd>(wCmd);
    _sendCommand(cast);
  }
}

void ClientControl::load(YolonaOss::GL::DrawSpecification* spec)
{
  _window = spec->getWindow();
}
