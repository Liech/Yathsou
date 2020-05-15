#pragma once

#include "VishalaNetworkLib/Core/Connection.h"

namespace Vishala {
  class LobbyModel;

  namespace Client {
    class LobbyClient {
    public:
      LobbyClient(std::unique_ptr < Connection > connection);

      void messageRecived(size_t player, size_t channel, std::unique_ptr<BinaryPackage> package);
      void newConnection(size_t clientnumber, std::string ip, int port);
      void connectionFailed(std::string name);
      void disconnect(size_t clientnumber);

      void update();
    private:
      std::unique_ptr<Connection> _connection;
    };
  }
}
