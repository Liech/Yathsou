#include "GameLobby.h"

#include "LobbyPlayer.h"
#include <iostream>

namespace Vishala {
  namespace Server {
    GameLobby::GameLobby(std::string name,int gameServerPort, std::string ip, size_t number, std::shared_ptr<LobbyModel> model) {
      _name           = name  ;
      _model          = model ;
      _number         = number;
      _gameServerPort = gameServerPort;
      _gameServerIP   = ip;
    }

    std::string GameLobby::getName() {
      return _name;
    }

    size_t GameLobby::getNumber() {
      return _number;
    }

    void GameLobby::addPlayer(std::shared_ptr<LobbyPlayer> player) {
      _participators[player->getID()] = player;
      sendUpdate();
    }

    void GameLobby::removePlayer(size_t playerID) {
      auto player = _participators[playerID];
      _participators.erase(playerID);
      player->leaveGame();
      sendUpdate();
    }

    void GameLobby::closeGame() {
      for (auto player : _participators) {
        player.second->leaveGame();
      }
    }

    size_t GameLobby::getNumberOfPlayers() {
      return _participators.size();
    }

    void GameLobby::sendUpdate() {
      GameLobbyStateUpdate update;
      update.currentPlayers.clear();
      std::cout << "Send GameLobby update: " << getName()<<std::endl;
      for (auto p : _participators){
        GameLobbyPlayer player;
        player.lobbyIdentification.name = p.second->getName();
        player.lobbyIdentification.color = p.second->getColor();
        player.lobbyIdentification.id   = p.first;     
        std::cout << "  " << player.lobbyIdentification.name << std::endl;
        update.currentPlayers.push_back(player);
      }
      update.gameName       = getName();
      update.gameStart      = _gameStarted;
      update.gameServerPort = _gameServerPort;
      update.gameServerIP   = _gameServerIP;

      for (auto p : _participators)
        p.second->sendGameLobbyUpdate(update);
    }

    void GameLobby::startGame() {
      std::cout << "GAME START" << std::endl;
      _gameStarted = true;
      sendUpdate();      
    }
  }
}