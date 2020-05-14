#include "GameLobby.h"

namespace Vishala {
  namespace Server {
    GameLobby::GameLobby(std::string name, size_t number) {
      _name = name;
      _number = number;
    }

    std::string GameLobby::getName() {
      return _name;
    }
  }
}