#pragma once

#include <memory>
#include <string>
#include <vector>
#include <set>
#include <map>

#include "VishalaNetworkLib/Core/Connection.h"

namespace Vishala {
  class ServerConfiguration;
  class Client2LobbyMessage;
  class CreateGameRequest;
  class JoinGameRequest;
  class LobbyModel;

  namespace Server {
    class LobbyPlayer;
    class GameLobby;

    class Lobby {
    public:
      Lobby(ServerConfiguration configurationFile);
      void update();

    private:
      void    newConnection(size_t clientnumber, std::string ip, int port);
      void    disconnect(size_t clientnumber);

      void    lobbyRequest(size_t player, Client2LobbyMessage request);

      void createGame(CreateGameRequest g, size_t playerNumber);
      void joinGame(JoinGameRequest g, size_t playerNumber);
      void closeGame(size_t playerNumber);
      void sendLobbyUpdate(size_t player);

      size_t  getNextPort();

      std::unique_ptr<Connection>                       _connection;
      std::shared_ptr<LobbyModel>                       _model     ;
      std::map<size_t, std::shared_ptr<LobbyPlayer>>    _players   ;
      std::map<size_t, size_t>                          _usedPorts ;
      std::map<size_t, std::shared_ptr<GameLobby>>      _games     ;

      size_t                                            _startPort   = 6556;
      size_t                                            _endPort     = 7556;
      size_t                                            _currentPort = 6556;
    };
  }
}