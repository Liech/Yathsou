#include "EnterLobby_Server.h"

#include "Connection.h"

namespace Vishala {
  EnterLobby_Server::EnterLobby_Server(std::function<void(std::shared_ptr<Protocoll>)> nextProtocollInvoked, std::unique_ptr<Connection> connection, std::string ip, int port) 
    : Protocoll(nextProtocollInvoked,std::move(connection)){

  }

  void EnterLobby_Server::messageRecived(size_t player, size_t channel, std::unique_ptr<BinaryPackage> package)
  {
  }

  void EnterLobby_Server::newConnection(size_t clientnumber, std::string ip, int port)
  {
  }

  void EnterLobby_Server::connectionFailed(std::string name)
  {
  }

  void EnterLobby_Server::disconnect(size_t clientnumber)
  {
  }

  void EnterLobby_Server::update()
  {
    Protocoll::update();
  }
}