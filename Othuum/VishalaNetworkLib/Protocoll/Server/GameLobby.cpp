#include "GameLobby.h"

#include "LobbyPlayer.h"

namespace Vishala {
  namespace Server {
    GameLobby::GameLobby(std::string name, size_t number, std::shared_ptr<LobbyModel> model) {
      _name   = name  ;
      _model  = model ;
      _number = number;
    }

    std::string GameLobby::getName() {
      return _name;
    }

    size_t GameLobby::getNumber() {
      return _number;
    }

    void GameLobby::addPlayer(std::shared_ptr<LobbyPlayer> player) {
      _participators[player->getID()] = player;
    }

    void GameLobby::closeGame() {
      for (auto player : _participators) {
        player.second->leaveGame();
      }
    }

    size_t GameLobby::getNumberOfPlayers() {
      return _participators.size();
    }

  }
}