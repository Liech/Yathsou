#include "LobbyConnector.h"

#include "Connection.h"
#include "Serializable/LoginInstructions.h"

namespace Vishala {
  LobbyConnector::LobbyConnector(std::string ip, int port,std::shared_ptr<Protocoll> next,std::function<void(std::shared_ptr<Protocoll>)> nextProtocollInvoked, std::unique_ptr<Connection> connection) 
    : Protocoll(nextProtocollInvoked,std::move(connection)){    
    _next = next;
    connect(port,ip);
  }

  void LobbyConnector::messageRecived(size_t player, size_t channel, std::unique_ptr<BinaryPackage> package)
  {
    assert(!_messageRecived);
    _messageRecived = true;

    LoginInstructions instructions;
    instructions.fromBinary(*package);
    _secondConnection = std::make_unique<Connection>();
    _secondConnection->setAcceptConnection(true);
    _secondConnection->setChannelCount(1);
    _secondConnection->setMaximumConnectionCount(1);
    _secondConnection->setPort(getPort()+1);
    _secondConnection->setNewConnectionCallback([this](size_t clientNumber, std::string ip, int port) { secondConnectionEstablished(); });
    _secondConnection->setConnectionFailedCallback([this](std::string ip) { handOver(nullptr); });
    _secondConnection->connect(instructions.port, instructions.ip);
  }

  void LobbyConnector::secondConnectionEstablished() {
    replaceConnection(std::move(_secondConnection));
    handOver(_next);    
  }

  void LobbyConnector::connectionFailed(std::string name)
  {
    _secondConnection = nullptr;
    handOver(nullptr);
  }

  void LobbyConnector::disconnect(size_t clientnumber)
  {
    _secondConnection = nullptr;
    handOver(nullptr);
  }

  void LobbyConnector::update()
  {
    if (_secondConnection != nullptr)
      _secondConnection->update();
    Protocoll::update();
  }
}