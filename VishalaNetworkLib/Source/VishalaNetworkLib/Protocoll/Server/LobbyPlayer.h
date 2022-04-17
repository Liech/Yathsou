#pragma once

#include <memory>
#include <string>
#include <functional>

#include "Core/Connection.h"
#include "Serializable/Client2LobbyMessage.h"
#include "Serializable/Lobby/LobbyModel.h"
#include "Serializable/Lobby2ClientMessage.h"

namespace Vishala {
  class BinaryPackage   ;
  class Connection      ;
  class LobbyRequestCall;
  class LobbyStateUpdate;
  class GameLobbyStateUpdate;
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

      std::string        getIP();
      std::string        getName();
      std::array<int, 3> getColor();

      void messageRecived(size_t player, size_t channel, std::unique_ptr<BinaryPackage> package);
      void newConnection(size_t clientnumber, std::string ip, int port);
      void connectionFailed(std::string name);
      void disconnect(size_t clientnumber);
      void update();
      LobbyPlayer::state getStatus() { return _state; }

      void gameHosted(std::shared_ptr<GameLobby> game);
      void joinGame(std::shared_ptr<GameLobby> game);
      void sendLobbyUpdate(const LobbyStateUpdate& msg);
      void sendGameLobbyUpdate(const GameLobbyStateUpdate& update);
      size_t getGameNumber();
      size_t getID() { return _playerNumber; }
      void leaveGame();

    private:
      LobbyStateUpdate getLobbyStateUpdate();

      void send(Lobby2ClientMessage* message);

      bool                         _connected = false;
      std::string                  _ip;
      LobbyPlayer::state           _state = state::Unintroduced;
      size_t                       _playerNumber;
      std::string                  _name;
      std::array<int, 3>           _color;

      std::unique_ptr<Connection>  _connection           ;
      std::shared_ptr<LobbyModel>  _model                ;
      std::shared_ptr<GameLobby>   _currentGame = nullptr;
    };
  }
}