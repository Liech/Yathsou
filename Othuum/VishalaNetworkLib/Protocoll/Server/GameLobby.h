#pragma once

#include <string>
#include <map>
#include <memory>

namespace Vishala {
  class LobbyModel;

  namespace Server {
    class LobbyPlayer;

    class GameLobby {
    public:
      GameLobby(std::string name, size_t gameNumber, std::shared_ptr<LobbyModel> model);

      std::string getName();
      size_t      getNumber();
      void        addPlayer(std::shared_ptr<LobbyPlayer> player);
      void        closeGame();
      void        removePlayer(size_t id);
      size_t      getNumberOfPlayers();

    private:
      void        sendUpdate();

      std::string                                       _name         ;
      size_t                                            _number       ;
      std::shared_ptr<LobbyModel>                       _model        ;
      std::map<size_t, std::shared_ptr<LobbyPlayer>>    _participators;
    };
  }
}