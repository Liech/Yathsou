#include "LobbyPlayer.h"

#include <chrono>
#include <thread>
#include <iostream>

#include "Serializable/LobbyBriefing.h"
#include "Serializable/SelfBriefing.h"
#include "Core/BinaryPackage.h"
#include "GameLobby.h"
#include "Serializable/Acknowledgement.h"

namespace Vishala {
  namespace Server {
    LobbyPlayer::LobbyPlayer(int myport, std::string ip, int port, size_t playerNumber, std::shared_ptr<LobbyModel> model) {
      _ip    = ip   ;
      _model = model;
      _playerNumber = playerNumber;
      std::cout << "LobbyChaperone: connect: " << ip << ":" << port << " (myPort: " << myport << ")" << std::endl;

      _connection = std::make_unique<Connection>();
      _connection->setAcceptConnection(true);
      _connection->setChannelCount(1);
      _connection->setMaximumConnectionCount(2);
      _connection->setPort(myport);
      _connection->setConnectionFailedCallback([this](std::string name) {connectionFailed(name); });
      _connection->setDisconnectCallback([this](size_t client) {disconnect(client); });
      _connection->setNewConnectionCallback([this](size_t client, std::string ip, int port) {newConnection(client, ip, port); });
      _connection->setRecievedCallback(0, [this](size_t client, std::unique_ptr<BinaryPackage> package) {messageRecived(client, 0, std::move(package)); });
      _connection->start();
      _connection->connect(port, ip);
    }

    void LobbyPlayer::messageRecived(size_t player, size_t channel, std::unique_ptr<BinaryPackage> package)
    {
      std::cout << "MSG" << std::endl;
      if (_state == LobbyPlayer::state::Unintroduced) {
        SelfBriefing description;
        description.fromBinary(*package);
        _state = LobbyPlayer::state::Lobby;
        std::cout << "He Is Known Now" << std::endl;
        LobbyBriefing briefing;
        briefing.lobbyStatus = getLobbyStateUpdate();
        briefing.playerId    = _playerNumber;
        send(&briefing);
        return;
      }
      else if (_state == LobbyPlayer::state::Lobby) {
        Client2LobbyRequest request;
        request.fromBinary(*package);
        if (request.type == Client2LobbyRequest::Type::CreateGame) {
          _model->openRequests.push_back(request);
        }
      }
    }

    void LobbyPlayer::newConnection(size_t clientnumber, std::string ip, int port)
    {
      std::cout << "Lobby Chaperone: new connection " << ip << ":" << port << std::endl;
      if (ip != _ip)
        throw std::runtime_error("Unexpected IP " + ip);
      _connected = true;
    }

    void LobbyPlayer::connectionFailed(std::string name)
    {
      std::cout << "Lobby Chaperone: connection failed " << name << std::endl;

    }

    void LobbyPlayer::disconnect(size_t clientnumber)
    {
      std::cout << "Lobby Chaperone: connection disconnect " << clientnumber << std::endl;

    }

    void LobbyPlayer::update()
    {
      _connection->update();
    }

    void LobbyPlayer::gameHosted(std::shared_ptr<GameLobby> game)
    {
      _currentGame = game;
      Acknowledgement ack;
      ack.type = Acknowledgement::Type::GameHosted;
      std::unique_ptr<BinaryPackage> package = std::make_unique<BinaryPackage>(ack.toBinary());
      _connection->send(0, 0, std::move(package));
    }

    LobbyStateUpdate LobbyPlayer::getLobbyStateUpdate() {
      LobbyStateUpdate result;
      result.openGames.clear();
      return result;
    }

    void LobbyPlayer::send(Serialization* message) {
      auto packet = message->toBinary();
      std::unique_ptr<BinaryPackage> p = std::make_unique<BinaryPackage>(packet);
      _connection->send(0, 0, std::move(p));
    }

  }
}