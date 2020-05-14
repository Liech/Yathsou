#pragma once

#include <string>
#include <map>
#include <memory>

namespace Vishala {
  namespace Server {
    class LobbyPlayer;

    class GameLobby {
    public:
      GameLobby(std::string name, size_t gameNumber);

      std::string getName();

    private:
      std::string                                       _name;
      size_t                                            _number;
      std::map<size_t, std::shared_ptr<LobbyPlayer>>    _participators;
    };
  }
}