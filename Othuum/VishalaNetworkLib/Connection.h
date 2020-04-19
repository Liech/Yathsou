#pragma once

#include <functional>
#include <vector>

#include "enet/enet.h"

namespace Vishala {
  class Connection {
  public:
     Connection();
    ~Connection();

    void start ();
    void stop  ();
    void update();

    void setChannelCount          (size_t numberOfChannels);
    void setMaximumConnectionCount(size_t max);
    void setAcceptConnection      (bool accept);
    void setPort                  (int port);

    void setNewConnectionCallback (                std::function<void(size_t clientnumber                                 )> func);
    void setDisconnectCallback    (                std::function<void(size_t clientnumber                                 )> func);
    void setRecievedCallback      (size_t channel, std::function<void(size_t clientNumber, uint8_t* package, size_t length)> func);


  private:
    ENetHost*   _connection             = nullptr;
    int         _numberOfConnections    = 1      ;
    int         _numberOfChannels       = 1      ;
    int         _port                   = 6112   ;
    bool        _acceptsConnections     = true   ;

    size_t      _clientNameCounter      = 0      ;
    
    std::function<void(size_t  clientNumber)>                                               _newConnection;
    std::function<void(size_t  clientNumber)>                                               _disconnect   ;
    std::vector<std::function<void(size_t  clientNumber, uint8_t* package, size_t length)>> _recived      ;
  };
}