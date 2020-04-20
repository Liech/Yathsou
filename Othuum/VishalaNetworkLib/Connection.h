#pragma once

#include <functional>
#include <vector>
#include <map>

#include "enet/enet.h"

namespace Vishala {

  class BinaryPackage;

  class Connection {
  public:
     Connection();
    ~Connection();

    void   start ();
    void   stop  ();
    void   update();
    size_t connect(int port, std::string ip); //returns -1 on failure
    void   send(size_t target, uint8_t channel, std::unique_ptr< BinaryPackage >, bool reliable = true);

    //config
    void setChannelCount          (uint8_t numberOfChannels);
    void setMaximumConnectionCount(size_t max);
    void setAcceptConnection      (bool accept);
    void setPort                  (int port);
    
    //config                     
    void setNewConnectionCallback (                 std::function<void(size_t clientnumber                                 )> func);
    void setDisconnectCallback    (                 std::function<void(size_t clientnumber                                 )> func);
    void setRecievedCallback      (uint8_t channel, std::function<void(size_t clientNumber, std::unique_ptr<BinaryPackage> )> func);


  private:
    ENetHost*   _connection             = nullptr;
    int         _numberOfConnections    = 1      ;
    uint8_t     _numberOfChannels       = 1      ;
    int         _port                   = 6112   ;
    bool        _acceptsConnections     = true   ;

    size_t      _clientNameCounter      = 0      ;
    
    std::function<void(size_t  clientNumber)>                                               _newConnection;
    std::function<void(size_t  clientNumber)>                                               _disconnect   ;
    std::vector<std::function<void(size_t  clientNumber, std::unique_ptr< BinaryPackage >)>> _recived      ;
    std::map<size_t, ENetPeer*>                                                             _peers        ;

    static inline size_t numberOfConnectsions = 0;
  };
}