#include "LobbyConnector.h"

#include "Serializable/LoginInstructions.h"
#include <iostream>
#include "Core/BinaryPackage.h"
#include "Serializable/SelfBriefing.h"

namespace Vishala {
  LobbyConnector::LobbyConnector(int myPort, std::string ip, int port){    
    _lobbyIP   = ip;
    _lobbyPort = port;
    _myPort    = myPort;
    _currentStatus = LobbyConnectorStatus::Waiting;

    _entryConnection = std::make_unique<Connection>();
    _entryConnection->setAcceptConnection(true);
    _entryConnection->setChannelCount(1);
    _entryConnection->setMaximumConnectionCount(2);
    _entryConnection->setPort(myPort);
    _entryConnection->setConnectionFailedCallback([this](std::string name) {connectionFailed(name); });
    _entryConnection->setDisconnectCallback([this](size_t client) {disconnect(client); });
    _entryConnection->setNewConnectionCallback([this](size_t client, std::string ip, int port) {newConnection(client, ip, port); });
    _entryConnection->setRecievedCallback(0, [this](size_t client, std::unique_ptr<BinaryPackage> package) {messageRecived(client, 0, std::move(package)); });
    _entryConnection->start();
    _entryConnection->connect(port, ip);
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
    _finalConnection = std::make_unique<Connection>();
    _finalConnection->setAcceptConnection(true);
    _finalConnection->setChannelCount(1);
    _finalConnection->setMaximumConnectionCount(2);
    _finalConnection->setPort(_myPort+1);
    _finalConnection->setNewConnectionCallback([this](size_t clientNumber, std::string ip, int port) {
      _currentStatus = LobbyConnectorStatus::ConnectionEstablished;
      std::cout << "LobbyConnectorStatus::ConnectionEstablished" << std::endl;
      });
    _finalConnection->setConnectionFailedCallback([this](std::string ip) {
      std::cout << "LobbyConnectorStatus::setConnectionFailedCallback" << std::endl;
      _disposed = true;
      });
    _finalConnection->start();
    std::cout << "LobbyConnectors: " << instructions.ip << ":" << instructions.port << " (myport: " << _myPort + 1<<")" << std::endl;

    _finalConnection->connect(instructions.port, instructions.ip);
  }

  void LobbyConnector::connectionFailed(std::string name)
  {
    _currentStatus = LobbyConnectorStatus::ConnectionFailed;
    std::cout << "LobbyConnectorStatus::ConnectionFailed" << std::endl;
  }

  void LobbyConnector::disconnect(size_t clientnumber)
  {
    _currentStatus = LobbyConnectorStatus::ConnectionFailed;
    std::cout << "LobbyConnectorStatus::ConnectionFailed" << std::endl;
  }

  void LobbyConnector::update()
  {
    if (_currentStatus == LobbyConnectorStatus::Extracted)
      throw std::runtime_error("Wrong Status");
    if (_entryConnection != nullptr)
      _entryConnection->update();
    if (_finalConnection != nullptr)
      _finalConnection->update();
  }
   
  LobbyConnectorStatus LobbyConnector::getStatus() {
    return _currentStatus;
  }

  std::unique_ptr<Connection> LobbyConnector::extractConnection() {
    if (_currentStatus != LobbyConnectorStatus::ConnectionEstablished)
      throw std::runtime_error("Wrong Status");

    SelfBriefing briefing;
    briefing.color = {rand()%256,rand()%256,rand()%256};
    briefing.name = "Horst";
    std::unique_ptr<BinaryPackage> package = std::make_unique<BinaryPackage>(briefing.toBinary());
    _finalConnection->send(0, 0, std::move(package));
    _currentStatus = LobbyConnectorStatus::Extracted;

    return std::move(_finalConnection);
  }

}