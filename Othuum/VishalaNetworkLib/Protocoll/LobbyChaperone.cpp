#include "LobbyChaperone.h"

#include "Serializable/LobbyBriefing.h"
#include "Serializable/SelfBriefing.h"
#include "Core/BinaryPackage.h"
#include <chrono>
#include <thread>
#include <iostream>

namespace Vishala {
  LobbyChaperone::LobbyChaperone(int myport, std::string ip, int port, size_t playerNumber, std::function<void(size_t, Client2LobbyRequest)> lobbyRequestCall){
    _ip               = ip              ;
    _lobbyRequestCall = lobbyRequestCall;
    _playerNumber     = playerNumber    ;
    std::cout << "LobbyChaperone: connect: " << ip << ":" << port << " (myPort: "<<myport<<")"<< std::endl;

    _connection = std::make_unique<Connection>();
    _connection->setAcceptConnection(true);
    _connection->setChannelCount(1);
    _connection->setMaximumConnectionCount(2);
    _connection->setPort(myport);
    _connection->setConnectionFailedCallback([this](std::string name) {connectionFailed(name); });
    _connection->setDisconnectCallback([this](size_t client) {disconnect(client); });
    _connection->setNewConnectionCallback([this](size_t client,std::string ip, int port) {newConnection(client,ip,port); });
    _connection->setRecievedCallback(0,[this](size_t client, std::unique_ptr<BinaryPackage> package) {messageRecived(client,0,std::move(package)); });
    _connection->start();
    _connection->connect(port, ip);
  }

  void LobbyChaperone::messageRecived(size_t player, size_t channel, std::unique_ptr<BinaryPackage> package)
  {
    std::cout << "MSG" << std::endl;
    if (_state == LobbyChaperone::state::Unintroduced) {
      SelfBriefing description;
      description.fromBinary(*package);
      _state = LobbyChaperone::state::Lobby;
      std::cout << "He Is Known Now"<<std::endl;
      return;
    }
    else if (_state == LobbyChaperone::state::Lobby){
      Client2LobbyRequest request;
      request.fromBinary(*package);
      if (request.type == Client2LobbyRequest::Type::CreateGame) {
        _lobbyRequestCall(_playerNumber, request);
      }
    }    
  }

  void LobbyChaperone::newConnection(size_t clientnumber, std::string ip, int port)
  {
    std::cout << "Lobby Chaperone: new connection " << ip<<":"<<port<<std::endl;
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
    std::cout << "Lobby Chaperone: connection failed " << name << std::endl;

  }

  void LobbyChaperone::disconnect(size_t clientnumber)
  {
    std::cout << "Lobby Chaperone: connection disconnect " << clientnumber << std::endl;

  }

  void LobbyChaperone::update()
  {
    _connection->update();
  }
}