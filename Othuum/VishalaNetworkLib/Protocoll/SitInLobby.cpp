#include "SitInLobby.h"

namespace Vishala {
  void SitInLobby::messageRecived(size_t player, size_t channel, std::unique_ptr<BinaryPackage> package)
  {
  }

  void SitInLobby::newConnection(size_t clientnumber, std::string ip, int port)
  {
  }

  void SitInLobby::connectionFailed(std::string name)
  {
  }

  void SitInLobby::disconnect(size_t clientnumber)
  {
  }

  void SitInLobby::update() {
    Protocoll::update();
  }
}