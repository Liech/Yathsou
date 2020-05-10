#pragma once

#include <string>
#include <memory>

#include "VishalaNetworkLib/Connection.h"


namespace Vishala {
  class Connection;
  class BinaryPackage;

  enum class LobbyConnectorStatus {
    ConnectionFailed,
    ConnectionEstablished,
    Waiting
  };

  //Lobby connector is the initial protocoll invoked to enter a lobby.
  //it asks the lobby for a port, generates a new connection to this port and invokes the next protocoll with the new connection  
  //connection should already has invoked start
  class LobbyConnector {
  public:
                                LobbyConnector(int myPort, std::string ip, int port);
    void                        update();                                
    LobbyConnectorStatus        getStatus();
    std::unique_ptr<Connection> extractConnection();
  private:
    void messageRecived(size_t player, size_t channel, std::unique_ptr<BinaryPackage> package);
    void newConnection(size_t clientnumber, std::string ip, int port) {}
    void connectionFailed(std::string name);
    void disconnect(size_t clientnumber);

    LobbyConnectorStatus _currentStatus;

    bool         _messageRecived   = false;
    bool         _disposed         = false;

    int         _lobbyPort;
    std::string _lobbyIP;

    std::unique_ptr<Connection> _entryConnection = nullptr;
    std::unique_ptr<Connection> _finalConnection = nullptr; //connects to the real target, not only to the lobby main port
  };
}