#include "LobbyClient.h"

namespace Vishala {
  namespace Client {
    LobbyClient::LobbyClient(std::unique_ptr<Connection> connection) {
      //First job of the server is to send us a lobby status update in response to the self briefing of the lobby connector. We will wait for this
      _connection = std::move(connection);
    }

    void LobbyClient::update() {
      _connection->update();
    }

    void LobbyClient::messageRecived(size_t player, size_t channel, std::unique_ptr<BinaryPackage> package) {

    }

    void LobbyClient::newConnection(size_t clientnumber, std::string ip, int port) {

    }

    void LobbyClient::connectionFailed(std::string name) {

    }

    void LobbyClient::disconnect(size_t clientnumber) {

    }

  }
}