#include "Lobby.h"

#include "Connection.h"
#include "BinaryPackage.h"
#include "ServerConfiguration.h"
#include "Protocoll/Protocoll.h"
#include "Protocoll/LobbyChaperone.h"

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
  }

  void Lobby::update()
  {
    _connection->update();
    for (auto protocoll : _protocolls)
      protocoll.second->update();
  }

  void Lobby::newConnection(size_t clientnumber, std::string ip, int incomingPort)
  {
    int port = getNextPort();
    std::unique_ptr<Connection> newConnection = std::make_unique<Connection>();
    newConnection->setAcceptConnection(true);
    newConnection->setChannelCount(1);
    newConnection->setPort(port);
    newConnection->start();

    std::shared_ptr< LobbyChaperone > startProtocoll = std::make_shared<LobbyChaperone>( ip, incomingPort,
      [this, clientnumber](std::shared_ptr<Protocoll> newProtocoll) { protocollReplaced(clientnumber, newProtocoll); }
      , std::move(newConnection));

    std::shared_ptr< Protocoll > cast = std::dynamic_pointer_cast<Protocoll>(startProtocoll);
    _protocolls[clientnumber] = cast;
    _usedPorts[clientnumber] = port;
  }

  void Lobby::disconnect(size_t clientnumber)
  {
    _protocolls.erase(clientnumber);
  }

  void Lobby::protocollReplaced(size_t player, std::shared_ptr<Protocoll> next) {
    _protocolls[player] = next;
  }

  size_t  Lobby::getNextPort() {
    while (_usedPorts.count(_currentPort) != 0) {
      _currentPort = (_currentPort + 1 - _startPort) % (_endPort - _startPort) + _startPort;
    }
    return _currentPort;
  }
}