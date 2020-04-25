#include "Lobby.h"

#include "Connection.h"
#include "BinaryPackage.h"
#include "ServerConfiguration.h"
#include "Protocoll/Protocoll.h"
#include "Protocoll/EnterLobby_Server.h"

namespace Vishala {
  Lobby::Lobby(ServerConfiguration configurationFile)
  {
    _connection = std::make_unique<Connection>();
    _connection->setAcceptConnection(true);
    _connection->setChannelCount(1);
    _connection->setPort(configurationFile.port);
    _connection->setConnectionFailedCallback([this](std::string name) {connectionFailed(name); });
    _connection->setDisconnectCallback      ([this](size_t client   ) {disconnect(client);     });
    _connection->setRecievedCallback        (0,[this](size_t client, std::unique_ptr<BinaryPackage> package) {recived(client, std::move(package));     });
    _connection->setNewConnectionCallback   ([this](size_t client)    {newConnection(client);  });
    _connection->start();    
  }

  void Lobby::update()
  {
    _connection->update();
  }

  void Lobby::newConnection(size_t clientnumber)
  {
    std::shared_ptr< EnterLobby_Server > startProtocoll = std::make_shared<EnterLobby_Server>();

    std::shared_ptr< Protocoll > cast = std::dynamic_pointer_cast<Protocoll>(startProtocoll);
    _protocolls[clientnumber] = cast;
  }

  void Lobby::connectionFailed(std::string name)
  {
  }

  void Lobby::disconnect(size_t clientnumber)
  {
  }

  void Lobby::recived(size_t clientNumber, std::unique_ptr<BinaryPackage> package)
  {
  }
}