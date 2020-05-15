#include "GameLobby.h"

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
  }
}