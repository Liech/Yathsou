#include "Lobby.h"

#include <iostream>

#include "Connection.h"
#include "BinaryPackage.h"
#include "ServerConfiguration.h"
#include "Protocoll/Protocoll.h"
#include "Protocoll/LobbyChaperone.h"
#include "Serializable/LoginInstructions.h"

namespace Vishala {
  Lobby::Lobby(ServerConfiguration configurationFile)
  {
    _connection = std::make_unique<Connection>();
    _connection->setAcceptConnection(true);
    _connection->setChannelCount(1);
    _connection->setMaximumConnectionCount(64);
    _connection->setPort(configurationFile.welcomePort);
    _connection->setConnectionFailedCallback(  [this](std::string name) {/*Lobby don't initiate connections*/});
    _connection->setDisconnectCallback      (  [this](size_t client   ) {disconnect(client);     });
    _connection->setRecievedCallback        (0,[this](size_t client, std::unique_ptr<BinaryPackage> package) {/*We don't care for messages in the main channel*/    });
    _connection->setNewConnectionCallback   (  [this](size_t client, std::string ip, int port)    {newConnection(client, ip, port);  });
    _connection->start();    
    std::cout << "Lobby awaiting connections"<<std::endl;
  }

  void Lobby::update()
  {
    _connection->update();
    std::vector<std::pair<size_t, std::shared_ptr<Protocoll>>> vec(_protocolls.begin(), _protocolls.end());
    for (auto protocoll : vec)
      protocoll.second->update();
  }

  void Lobby::newConnection(size_t clientnumber, std::string ip, int incomingPort)
  {
    std::cout << "Lobby::newConnection " << clientnumber << " - "<< ip << ":" << incomingPort<<std::endl;
    int port = getNextPort();
    
    LoginInstructions instructions;
    instructions.ip = "SAME";
    instructions.port = port;
    std::unique_ptr<BinaryPackage> package = std::make_unique<BinaryPackage>(instructions.toBinary());
    _connection->send(clientnumber, 0, std::move(package));
    
    std::unique_ptr<Connection> newConnection = std::make_unique<Connection>();
    newConnection->setAcceptConnection(true);
    newConnection->setChannelCount(1);
    newConnection->setMaximumConnectionCount(2);
    newConnection->setPort(port);
    newConnection->start();

    std::shared_ptr< LobbyChaperone > startProtocoll = std::make_shared<LobbyChaperone>( ip, port,
      [this, clientnumber](std::shared_ptr<Protocoll> newProtocoll) { protocollReplaced(clientnumber, newProtocoll); }
      , std::move(newConnection));

    std::shared_ptr< Protocoll > cast = std::dynamic_pointer_cast<Protocoll>(startProtocoll);
    _protocolls[clientnumber] = cast;
    _usedPorts[clientnumber] = port;
  }

  void Lobby::disconnect(size_t clientnumber)
  {
    std::cout << "Lobby::disconnect " << clientnumber << std::endl;
    _protocolls.erase(clientnumber);
  }

  void Lobby::protocollReplaced(size_t player, std::shared_ptr<Protocoll> next) {
    if (next == nullptr){
      std::cout << "Lobby::protocollReplaced " << _protocolls[player]->getName() << " -> " << "nothing" << std::endl;
      _protocolls.erase(player);
    }
    else {
      std::cout << "Lobby::protocollReplaced " << _protocolls[player]->getName() << " -> " << next->getName() << std::endl;
      _protocolls[player] = next;
    }
  }

  size_t  Lobby::getNextPort() {
    while (_usedPorts.count(_currentPort) != 0) {
      _currentPort = (_currentPort + 1 - _startPort) % (_endPort - _startPort) + _startPort;
    }
    return _currentPort;
  }
}