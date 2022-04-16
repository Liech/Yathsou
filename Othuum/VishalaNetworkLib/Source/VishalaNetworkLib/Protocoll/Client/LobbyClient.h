#pragma once

#include "VishalaNetworkLib/Core/Connection.h"
#include "VishalaNetworkLib/Serializable/Client2LobbyMessage.h"
#include "VishalaNetworkLib/Serializable/LobbyStateUpdate.h"
#include "VishalaNetworkLib/Serializable/GameLobbyStateUpdate.h"

namespace Vishala {
  class LobbyModel;

  namespace Client {
    class LobbyClient {
    public:
      enum class Status {
        Disconnected, Lobby, GameHostRequested, GameHosted, GameJoinRequested, GameJoined
      };

      LobbyClient(std::unique_ptr < Connection > connection);

      LobbyClient::Status getStatus();

      void                hostGame(Vishala::CreateGameRequest options);
      void                joinGame(size_t gameID);
      void                closeGame();
      void                requestRefresh();
      void                startGameRequest();

      void messageRecived  (size_t player, size_t channel, std::unique_ptr<BinaryPackage> package);
      void newConnection   (size_t clientnumber, std::string ip, int port);
      void connectionFailed(std::string name);
      void disconnect      (size_t clientnumber);

      void update();
      void stop();
      std::unique_ptr<Vishala::LobbyStateUpdate>     getLobbyStateUpdate();
      std::unique_ptr<Vishala::GameLobbyStateUpdate> getGameLobbyStateUpdate();
    private:
      void sendMessage(Vishala::Client2LobbyMessage);

      std::unique_ptr<Connection>                    _connection;
      LobbyClient::Status                            _status    = Status::Lobby;
      std::unique_ptr<Vishala::LobbyStateUpdate>     _lobbyStateUpdate = nullptr;
      std::unique_ptr<Vishala::GameLobbyStateUpdate> _gameLobbyStateUpdate = nullptr;
    };
  }
}
