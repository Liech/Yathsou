#include "Lobby.h"

#include <iostream>

#include "Core/Connection.h"
#include "Core/BinaryPackage.h"
#include "Serializable/ServerConfiguration.h"
#include "Protocoll/Server/LobbyPlayer.h"
#include "Serializable/LoginInstructions.h"
#include "Serializable/Client2LobbyMessage.h"
#include "GameLobby.h"
#include "Serializable/Lobby/LobbyModel.h"

namespace Vishala {
  namespace Server {
    Lobby::Lobby(ServerConfiguration configurationFile)
    {
      _model = std::make_shared<LobbyModel>();

      _connection = std::make_unique<Connection>();
      _connection->setAcceptConnection(true);
      _connection->setChannelCount(1);
      _connection->setMaximumConnectionCount(64);
      _connection->setPort(configurationFile.welcomePort);
      _connection->setConnectionFailedCallback([this](std::string name) {/*Lobby don't initiate connections*/});
      _connection->setDisconnectCallback([this](size_t client) {disconnect(client);     });
      _connection->setRecievedCallback(0, [this](size_t client, std::unique_ptr<BinaryPackage> package) {/*We don't care for messages in the main channel*/    });
      _connection->setNewConnectionCallback([this](size_t client, std::string ip, int port) {newConnection(client, ip, port);  });
      bool ok = _connection->start();
      if (!ok)
        throw std::runtime_error("Port used");
      std::cout << "Lobby awaiting connections" << std::endl;
    }

    void Lobby::update()
    {
      _connection->update();
      std::vector<std::pair<size_t, std::shared_ptr<LobbyPlayer>>> vec(_players.begin(), _players.end());
      for (auto protocoll : vec) {
        if (protocoll.second->getStatus() != LobbyPlayer::state::Disconnected)
          protocoll.second->update();
        else {
          disconnect(protocoll.first);
          return;
        }
      }
      for (auto request : _model->openRequests) {
        if (request.request.type == Client2LobbyMessage::Type::CreateGame||
            request.request.type == Client2LobbyMessage::Type::CloseGame)
          lobbyRequest(request.playerNumber, request.request);
      }
      _model->openRequests.clear();

    }

    void Lobby::newConnection(size_t clientnumber, std::string ip, int incomingPort)
    {
      std::cout << "Lobby::newConnection " << clientnumber << " - " << ip << ":" << incomingPort << std::endl;
      int port = getNextPort();

      LoginInstructions instructions;
      instructions.ip = "SAME";
      instructions.port = port;
      std::unique_ptr<BinaryPackage> package = std::make_unique<BinaryPackage>(instructions.toBinary());
      _connection->send(clientnumber, 0, std::move(package));

      std::shared_ptr< LobbyPlayer > startProtocoll = std::make_shared<LobbyPlayer>(port, ip, incomingPort + 1, _model->nextPlayerNumber,_model);
      std::shared_ptr< LobbyPlayer > cast = std::dynamic_pointer_cast<LobbyPlayer>(startProtocoll);
      _players[_model->nextPlayerNumber] = startProtocoll;
      _usedPorts[_model->nextPlayerNumber] = port;
      _model->nextPlayerNumber++;
    }

    void Lobby::disconnect(size_t clientnumber)
    {
      std::cout << "Lobby::disconnect " << clientnumber << std::endl;
      if (_players.count(clientnumber))
        _players.erase(clientnumber);
    }

    size_t  Lobby::getNextPort() {
      while (_usedPorts.count(_currentPort) != 0) {
        _currentPort = (_currentPort + 1 - _startPort) % (_endPort - _startPort) + _startPort;
      }
      return _currentPort;
    }

    void Lobby::lobbyRequest(size_t player, Client2LobbyMessage request) {
      if (request.type == Client2LobbyMessage::Type::CreateGame)
        createGame(request.createGame, player);      
      else if (request.type == Client2LobbyMessage::Type::Refresh)
        sendLobbyUpdate(player);
    }

    void Lobby::sendLobbyUpdate(size_t player) {
      LobbyStateUpdate msg;
      msg.openGames.clear();
      for (auto game : _games) {
        LobbyGame gameDesc;
        gameDesc.maxNumberOfPlayers = 32;
        gameDesc.name = game.second->getName();
        gameDesc.numberOfPlayers = game.second->getNumberOfPlayers();
        msg.openGames.push_back(gameDesc);
      }
      _players[player]->sendLobbyUpdate(msg);
    }

    void Lobby::createGame(CreateGameRequest content, size_t playerNumber) {
      std::shared_ptr<GameLobby> game = std::make_shared<GameLobby>(content.gameName, _model->nextGameNumber, _model);
      _games[_model->nextGameNumber] = game;
      _players[playerNumber]->gameHosted(game);
      game->addPlayer(_players[playerNumber]);
      _model->nextGameNumber++;
    }

    void Lobby::closeGame(size_t playerNumber) {
      std::cout << "Game Closed" << std::endl;
      size_t number = _players[playerNumber]->getGameNumber();
      std::shared_ptr<GameLobby> game = _games[number];
      _games.erase(number);
      game->closeGame();
    }

  }
}