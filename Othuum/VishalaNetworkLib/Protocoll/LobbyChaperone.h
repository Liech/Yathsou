#pragma once

#include <memory>
#include <string>

#include "Connection.h"

namespace Vishala {
  class BinaryPackage;
  class Connection;

  //used by lobby to make one single client happy
  class LobbyChaperone {
    enum class state {
      HeIsUnkown, HeIsKnown
    };
  public:
    LobbyChaperone(int myport, std::string ip, int port, size_t playerNumber);

    virtual std::string getName() { return "LobbyChaperone"; }

    void messageRecived  (size_t player, size_t channel, std::unique_ptr<BinaryPackage> package);
    void newConnection   (size_t clientnumber, std::string ip, int port                        );
    void connectionFailed(std::string name                                                     );
    void disconnect      (size_t clientnumber                                                  );
    void update          (                                                                     );
  private:
    bool          _connected = false;
    std::string   _ip               ;    
    LobbyChaperone::state _state = state::HeIsUnkown;

    std::unique_ptr<Connection> _connection;
  };
}