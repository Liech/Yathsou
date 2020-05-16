#include "LobbyClient.h"

#include <iostream>

#include "Serializable/Client2LobbyMessage.h"

namespace Vishala {
  namespace Client {
    LobbyClient::LobbyClient(std::unique_ptr<Connection> connection) {
      //First job of the server is to send us a lobby status update in response to the self briefing of the lobby connector. We will wait for this
      _connection = std::move(connection);
    }

    void LobbyClient::update() {
      _connection->update();
    }

    LobbyClient::Status LobbyClient::getStatus() {
      return _status;
    }

    void LobbyClient::messageRecived(size_t player, size_t channel, std::unique_ptr<BinaryPackage> package) {

    }

    void LobbyClient::newConnection(size_t clientnumber, std::string ip, int port) {
      _status = LobbyClient::Status::Disconnected;
    }

    void LobbyClient::connectionFailed(std::string name) {
      _status = LobbyClient::Status::Disconnected;

    }

    void LobbyClient::disconnect(size_t clientnumber) {
      _status = LobbyClient::Status::Disconnected;
    }

    void LobbyClient::hostGame(std::string name) {
      if (_status != LobbyClient::Status::Lobby)
        throw std::runtime_error("Can't host when not in Lobby");
      std::cout << "Send host request: " << name << std::endl;
      Client2LobbyMessage request;
      request.type                = Client2LobbyMessage::Type::CreateGame;     
      request.createGame.gameName = name;
      std::unique_ptr<BinaryPackage> package = std::make_unique<BinaryPackage>(request.toBinary());
      _connection->send(0,0,std::move(package));
      _status = LobbyClient::Status::GameHostRequested;
    }

  }
}