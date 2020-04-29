#include "LobbyConnector.h"

#include "Connection.h"
#include "Serializable/LoginInstructions.h"
#include <iostream>

namespace Vishala {
  LobbyConnector::LobbyConnector(std::string ip, int port,std::shared_ptr<Protocoll> next,std::function<void(std::shared_ptr<Protocoll>)> nextProtocollInvoked, std::unique_ptr<Connection> connection) 
    : Protocoll(nextProtocollInvoked,std::move(connection)){    
    _lobbyIP   = ip;
    _lobbyPort = port;
    _next = next;
    connect(port,ip);
  }

  void LobbyConnector::messageRecived(size_t player, size_t channel, std::unique_ptr<BinaryPackage> package)
  {
    assert(!_messageRecived);
    _messageRecived = true;
    
    LoginInstructions instructions;
    instructions.fromBinary(*package);
    if (instructions.ip == "SAME")
      instructions.ip = _lobbyIP;
    std::cout << "Recived LoginInstructions: " << instructions.ip << ":" << instructions.port << std::endl;
    _secondConnection = std::make_unique<Connection>();
    _secondConnection->setAcceptConnection(true);
    _secondConnection->setChannelCount(1);
    _secondConnection->setMaximumConnectionCount(2);
    _secondConnection->setPort(getPort()+1);
    _secondConnection->setNewConnectionCallback([this](size_t clientNumber, std::string ip, int port) {
      secondConnectionEstablished();
      });
    _secondConnection->setConnectionFailedCallback([this](std::string ip) {
      _disposed = true;
      handOver(nullptr);
      });
    _secondConnection->start();
    std::cout << "TRY CONNECT" << instructions.ip << ":" << instructions.port << std::endl;
    _secondConnection->connect(instructions.port, instructions.ip);
  }

  void LobbyConnector::secondConnectionEstablished() {
    std::cout << "Second connection is established" << std::endl;
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
    if (!_disposed)
      Protocoll::update();
  }
}