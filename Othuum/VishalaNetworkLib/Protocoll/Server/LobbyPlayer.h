#pragma once

#include <memory>
#include <string>
#include <functional>

#include "Core/Connection.h"
#include "Serializable/Client2LobbyMessage.h"
#include "Serializable/Lobby/LobbyModel.h"

namespace Vishala {
  class BinaryPackage   ;
  class Connection      ;
  class LobbyRequestCall;
  class LobbyStateUpdate;
}

namespace Vishala {
  namespace Server {
    class GameLobby;

    //used by lobby to make one single client happy
    class LobbyPlayer {
    public:
      enum class state {
        Unintroduced, Lobby, Host, Joined, Disconnected
      };
      LobbyPlayer(int myport, std::string ip, int port, size_t playerNumber, std::shared_ptr<LobbyModel> model);

      virtual std::string getName() { return "LobbyChaperone"; }

      void messageRecived(size_t player, size_t channel, std::unique_ptr<BinaryPackage> package);
      void newConnection(size_t clientnumber, std::string ip, int port);
      void connectionFailed(std::string name);
      void disconnect(size_t clientnumber);
      void update();
      LobbyPlayer::state getStatus() { return _state; }

      void gameHosted(std::shared_ptr<GameLobby> game);

    private:
      LobbyStateUpdate getLobbyStateUpdate();

      void send(Serialization* message);

      bool                         _connected = false;
      std::string                  _ip;
      LobbyPlayer::state           _state = state::Unintroduced;
      size_t                       _playerNumber;

      std::unique_ptr<Connection>  _connection           ;
      std::shared_ptr<LobbyModel>  _model                ;
      std::shared_ptr<GameLobby>   _currentGame = nullptr;
    };
  }
}