#include "ClientControl.h"

#include "AhwassaGraphicsLib/Core/Window.h"
#include "AhwassaGraphicsLib/Input/Input.h"
#include "UyanahGameServer/Commands/Key.h"

ClientControl::ClientControl(std::function<void(std::shared_ptr<Vishala::ICommand>)> sendCommand,
  std::shared_ptr<const Uyanah::Scene> scene, Ahwassa::Window* w) {
  _scene = scene;
  _sendCommand = sendCommand;
  _window = w;
}  
ClientControl::ClientControl(Ahwassa::Window*w)  {
  _window = w;
}


void ClientControl::update() {
  bool w = _window->input().getKeyStatus(Iyathuum::Key::KEY_W) == Iyathuum::KeyStatus::PRESS;
  bool a = _window->input().getKeyStatus(Iyathuum::Key::KEY_A) == Iyathuum::KeyStatus::PRESS;
  bool s = _window->input().getKeyStatus(Iyathuum::Key::KEY_S) == Iyathuum::KeyStatus::PRESS;
  bool d = _window->input().getKeyStatus(Iyathuum::Key::KEY_D) == Iyathuum::KeyStatus::PRESS;

  if (w != _w)
  {
    auto wCmd = std::make_shared<Uyanah::Commands::KeyCmd>();
    wCmd->key = Iyathuum::Key::KEY_W;
    wCmd->status = w ? Iyathuum::KeyStatus::PRESS : Iyathuum::KeyStatus::RELEASE;
    std::shared_ptr<Vishala::ICommand> cast = std::static_pointer_cast<Uyanah::Commands::KeyCmd>(wCmd);
    _sendCommand(cast);
  }
  if (a != _a)
  {
    auto wCmd = std::make_shared<Uyanah::Commands::KeyCmd>();
    wCmd->key = Iyathuum::Key::KEY_A;
    wCmd->status = a ? Iyathuum::KeyStatus::PRESS : Iyathuum::KeyStatus::RELEASE;
    std::shared_ptr<Vishala::ICommand> cast = std::static_pointer_cast<Uyanah::Commands::KeyCmd>(wCmd);
    _sendCommand(cast);
  }
  if (s != _s)
  {
    auto wCmd = std::make_shared<Uyanah::Commands::KeyCmd>();
    wCmd->key = Iyathuum::Key::KEY_S;
    wCmd->status = s ? Iyathuum::KeyStatus::PRESS : Iyathuum::KeyStatus::RELEASE;
    std::shared_ptr<Vishala::ICommand> cast = std::static_pointer_cast<Uyanah::Commands::KeyCmd>(wCmd);
    _sendCommand(cast);
  }
  if (d!=_d)
  {
    auto wCmd = std::make_shared<Uyanah::Commands::KeyCmd>();
    wCmd->key = Iyathuum::Key::KEY_D;
    wCmd->status = d ? Iyathuum::KeyStatus::PRESS : Iyathuum::KeyStatus::RELEASE;
    std::shared_ptr<Vishala::ICommand> cast = std::static_pointer_cast<Uyanah::Commands::KeyCmd>(wCmd);
    _sendCommand(cast);
  }

  _w = w; 
  _a = a; 
  _s = s; 
  _d = d; 
}
