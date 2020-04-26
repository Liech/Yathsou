#include "EnterLobby.h"

#include "Serializable/SelfBriefing.h"

namespace Vishala {
  EnterLobby::EnterLobby() {

  }

  void EnterLobby::messageRecived(size_t player, size_t channel, std::unique_ptr<BinaryPackage> package)
  {
  }

  void EnterLobby::newConnection(size_t clientnumber, std::string ip, int port)
  {
  }

  void EnterLobby::connectionFailed(std::string name)
  {
  }

  void EnterLobby::disconnect(size_t clientnumber)
  {
  }

  void EnterLobby::update()
  {
  }

  void EnterLobby::initialization() {
    SelfBriefing toSend;
    toSend.color = {rand() * 255, rand()*255,rand()*255};
    toSend.name = "Horst";
    std::unique_ptr<BinaryPackage> package = std::make_unique<BinaryPackage>(toSend.toBinary());    
    sendMessage(0,0,std::move(package));
  }
}