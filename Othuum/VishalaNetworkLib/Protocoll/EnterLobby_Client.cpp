#include "EnterLobby_Client.h"


namespace Vishala {
  void EnterLobby_Client::messageRecived(size_t player, size_t channel, std::unique_ptr<BinaryPackage> package)
  {
  }

  void EnterLobby_Client::newConnection(size_t clientnumber, std::string ip, int port)
  {
  }

  void EnterLobby_Client::connectionFailed(std::string name)
  {
  }

  void EnterLobby_Client::disconnect(size_t clientnumber)
  {
  }

  void EnterLobby_Client::update()
  {
  }
}