#include "LobbyChaperone.h"

#include "Serializable/LobbyBriefing.h"
#include "Serializable/SelfBriefing.h"
#include "BinaryPackage.h"

#include <iostream>

namespace Vishala {
  LobbyChaperone::LobbyChaperone(std::string ip, int port, size_t playerNumber){
    _ip = ip;
    std::cout << "LobbyChaperone: connect: " << ip << ":" << port << std::endl;

    _connection = std::make_unique<Connection>();
    _connection->setAcceptConnection(true);
    _connection->setChannelCount(1);
    _connection->setMaximumConnectionCount(2);
    _connection->setPort(port);
    _connection->setConnectionFailedCallback([this](std::string name) {connectionFailed(name); });
    _connection->setDisconnectCallback([this](size_t client) {disconnect(client); });
    _connection->setNewConnectionCallback([this](size_t client,std::string ip, int port) {newConnection(client,ip,port); });
    _connection->setRecievedCallback(0,[this](size_t client, std::unique_ptr<BinaryPackage> package) {messageRecived(client,0,std::move(package)); });
    _connection->start();
    _connection->connect(port, ip);
  }

  void LobbyChaperone::messageRecived(size_t player, size_t channel, std::unique_ptr<BinaryPackage> package)
  {
    if (_state == LobbyChaperone::state::HeIsUnkown) {
      SelfBriefing description;
      description.fromBinary(*package);
      _state = LobbyChaperone::state::HeIsKnown;
      std::cout << "He Is Known Now"<<std::endl;
    }
  }

  void LobbyChaperone::newConnection(size_t clientnumber, std::string ip, int port)
  {
    if (ip != _ip)
      throw std::runtime_error("Unexpected IP " + ip);
    _connected = true;
    LobbyBriefing briefing;
    auto packet = briefing.toBinary();
    std::unique_ptr<BinaryPackage> p = std::make_unique<BinaryPackage>(packet);    
    _connection->send(0, 0, std::move(p));
  }

  void LobbyChaperone::connectionFailed(std::string name)
  {

  }

  void LobbyChaperone::disconnect(size_t clientnumber)
  {

  }

  void LobbyChaperone::update()
  {
    _connection->update();
  }
}