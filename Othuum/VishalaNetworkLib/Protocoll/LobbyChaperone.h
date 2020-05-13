#pragma once

#include <memory>
#include <string>
#include <functional>

#include "Core/Connection.h"
#include "Serializable/Client2LobbyRequest.h"

namespace Vishala {
  class BinaryPackage   ;
  class Connection      ;
  class LobbyRequestCall;

  //used by lobby to make one single client happy
  class LobbyChaperone {
    enum class state {
      Unintroduced, Lobby, Host, Joined
    };
  public:
    LobbyChaperone(int myport, std::string ip, int port, size_t playerNumber, std::function<void(size_t, Client2LobbyRequest)> lobbyRequestCall);

    virtual std::string getName() { return "LobbyChaperone"; }

    void messageRecived  (size_t player, size_t channel, std::unique_ptr<BinaryPackage> package);
    void newConnection   (size_t clientnumber, std::string ip, int port                        );
    void connectionFailed(std::string name                                                     );
    void disconnect      (size_t clientnumber                                                  );
    void update          (                                                                     );

  private:
    bool                         _connected = false          ;
    std::string                  _ip                         ;    
    LobbyChaperone::state        _state = state::Unintroduced;
    size_t                       _playerNumber               ;

    std::unique_ptr<Connection>                     _connection      ;
    std::function<void(size_t,Client2LobbyRequest)> _lobbyRequestCall;
  };
}