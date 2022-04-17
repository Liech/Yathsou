#pragma once

#include <string>
#include <map>
#include <memory>

namespace Vishala {
  class LobbyModel;

  namespace Server {
    class LobbyPlayer;

    class GameServer{};

    class GameLobby {
    public:
      GameLobby(std::string name,int gameServerPort, std::string ip, size_t gameNumber, std::shared_ptr<LobbyModel> model);

      std::string getName();
      size_t      getNumber();
      void        addPlayer(std::shared_ptr<LobbyPlayer> player);
      void        closeGame();
      void        removePlayer(size_t id);
      size_t      getNumberOfPlayers();
      void        startGame();

    private:
      void        sendUpdate();

      std::string                                       _gameServerIP = "localhost";
      int                                               _gameServerPort = 0;
      bool                                              _gameStarted  = false;
      std::string                                       _name         ;
      size_t                                            _number       ;
      std::shared_ptr<LobbyModel>                       _model        ;
      std::map<size_t, std::shared_ptr<LobbyPlayer>>    _participators;
    };
  }
}