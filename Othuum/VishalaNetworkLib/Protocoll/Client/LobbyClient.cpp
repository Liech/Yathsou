#include "LobbyClient.h"

#include <iostream>

#include "Serializable/Client2LobbyMessage.h"
#include "Serializable/Lobby2ClientMessage.h" 

namespace Vishala {
  namespace Client {
    LobbyClient::LobbyClient(std::unique_ptr<Connection> connection) {
      //First job of the server is to send us a lobby status update in response to the self briefing of the lobby connector. We will wait for this
      _connection = std::move(connection);
      _connection->setConnectionFailedCallback([](std::string name) {throw std::runtime_error("Connection cannot fail, but failed. New Connections are not allowed"); });
      _connection->setDisconnectCallback([this](size_t num) {disconnect(num); });
      _connection->setNewConnectionCallback([](size_t num, std::string name, int port) {throw std::runtime_error("New Connections are not allowed"); });
      _connection->setRecievedCallback(0,[this](size_t player, std::unique_ptr<BinaryPackage> package) {messageRecived(player, 0, std::move(package)); });

      std::cout << "Lobby Client Initialized" << std::endl;
      _lobbyStateUpdate = nullptr;
    }

    void LobbyClient::update() {
      _connection->update();
    }

    LobbyClient::Status LobbyClient::getStatus() {
      return _status;
    }

    void LobbyClient::messageRecived(size_t player, size_t channel, std::unique_ptr<BinaryPackage> package) {
      Lobby2ClientMessage msg;
      msg.fromBinary(*package);
      std::cout << "MSG RECIVED: " <<(int)msg.type<< std::endl;
      if (msg.type == Lobby2ClientMessage::Type::Acknowledgment) {
        if (msg.acknowledgment.type == Acknowledgement::Type::GameHosted) {
          if (_status == LobbyClient::Status::GameHostRequested) {
            _status = LobbyClient::Status::GameHosted;
            std::cout << "Game Host Acknowledgement recived" << std::endl;
          }

          else
            throw std::runtime_error("Unexpected Host Acknowledgement");
        }
        else if (msg.acknowledgment.type == Acknowledgement::Type::GameJoined) {
          if (_status == LobbyClient::Status::GameJoinRequested) {
            _status = LobbyClient::Status::GameJoined;
            std::cout << "Game Join Acknowledgement recived" << std::endl;
          }
          else
            throw std::runtime_error("Unexpected Join Acknowledgement");
        }

      }
      else if (msg.type == Lobby2ClientMessage::Type::LobbyUpdate) {
        _lobbyStateUpdate = std::make_unique<Vishala::LobbyStateUpdate>(msg.lobbyUpdate);
      }
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

    void LobbyClient::hostGame(Vishala::CreateGameRequest options) {
      if (_status != LobbyClient::Status::Lobby)
        throw std::runtime_error("Can't host when not in Lobby");
      std::cout << "Send host request: " << options.gameName << std::endl;
      Client2LobbyMessage request;
      request.type       = Client2LobbyMessage::Type::CreateGame;     
      request.createGame = options;
      
      sendMessage(request);
      _status = LobbyClient::Status::GameHostRequested;
    }

    void LobbyClient::joinGame(size_t gameID) {
      if (_status != LobbyClient::Status::Lobby)
        throw std::runtime_error("Can't join when not in Lobby");
      std::cout << "Send join request: " << gameID << std::endl;
      Client2LobbyMessage request;
      request.type = Client2LobbyMessage::Type::JoinGame;
      request.joinGame.gameID = gameID;

      sendMessage(request);
      _status = LobbyClient::Status::GameJoinRequested;
    }

    void LobbyClient::closeGame() {
      if (_status != LobbyClient::Status::GameHosted)
        throw std::runtime_error("wrong status");
      std::cout << "Close game" << std::endl;
      Client2LobbyMessage request;
      request.type = Client2LobbyMessage::Type::LeaveGame;
      sendMessage(request);
      _status = LobbyClient::Status::Lobby;
    }

    void LobbyClient::stop() {
      if (_connection)
        _connection->stop();
      _lobbyStateUpdate = nullptr;
    }

    void LobbyClient::sendMessage(Vishala::Client2LobbyMessage msg) {
      std::unique_ptr<BinaryPackage> package = std::make_unique<BinaryPackage>(msg.toBinary());
      _connection->send(0, 0, std::move(package));
    }
    
    void LobbyClient::requestRefresh() {
      Vishala::Client2LobbyMessage msg;
      msg.type = Vishala::Client2LobbyMessage::Type::Refresh;
      sendMessage(msg);
    }

    std::unique_ptr<Vishala::LobbyStateUpdate> LobbyClient::getLobbyStateUpdate() {
      if (_lobbyStateUpdate != nullptr) {
        auto result = std::move(_lobbyStateUpdate);
        _lobbyStateUpdate = nullptr;
        return std::move(result);
      }
      return nullptr;
    }
  }
}