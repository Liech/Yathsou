#pragma once

#include <memory>
#include <string>
#include <vector>
#include <set>
#include <map>

#include "Connection.h"

namespace Vishala {
  class BinaryPackage;
  class ServerConfiguration;
  class Protocoll;

  class Lobby {
  public:
    Lobby(ServerConfiguration configurationFile);
    void update();

  private:
    void    newConnection   (size_t clientnumber, std::string ip, int port      );
    void    disconnect      (size_t clientnumber                                );
    void    protocollReplaced(size_t player, std::shared_ptr<Protocoll> next    );
    
    size_t  getNextPort();


    std::unique_ptr<Connection>                  _connection;
    std::map<size_t, std::shared_ptr<Protocoll>> _protocolls;
    std::map<size_t,size_t>                      _usedPorts ;

    size_t                                       _startPort   = 6556;
    size_t                                       _endPort     = 7556;
    size_t                                       _currentPort = 6556;
  };
}