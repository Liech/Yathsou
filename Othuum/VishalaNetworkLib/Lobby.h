#pragma once

#include <memory>
#include <string>
#include <vector>
#include <map>

namespace Vishala {
  class Connection;
  class BinaryPackage;
  class ServerConfiguration;
  class Protocoll;

  class Lobby {
    Lobby(ServerConfiguration configurationFile);
    void update();

  private:
    void newConnection   (size_t clientnumber);
    void connectionFailed(std::string name   );
    void disconnect      (size_t clientnumber);
    void recived         (size_t clientNumber, std::unique_ptr<BinaryPackage>);


    std::unique_ptr<Connection>                  _connection;
    std::map<size_t, std::shared_ptr<Protocoll>> _protocolls;
    std::map<size_t, int>                        _usedPorts ;
  };
}