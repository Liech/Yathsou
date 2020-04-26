#pragma once

#include <functional>
#include <vector>
#include <map>
#include <future>

#include "lib/enet/enet.h"
#include "lib/concurrentqueue.h"

#include "BinaryPackage.h"

namespace Vishala {
  class Connection {
    class NetReciveEvent {
    public:
      ENetEventType              type                 ;
      std::vector<unsigned char> data                 ;
      size_t                     player               ;
      size_t                     channel              ;      
      bool                       newConnection = false;
      std::string                targetIP             ;
      int                        port                 ;
      bool                       connectionSuccess    ;
    };
    class NetSendEvent {
    public:
      enum class Type { disconnect, send, connect };
      NetSendEvent::Type               type    ;
      std::vector<unsigned char>       data    ;
      size_t                           channel ;
      size_t                           target  ;
      bool                             reliable;
      std::string                      ip      ;
      int                              port    ;
    };
  public:
     Connection();
    ~Connection();

    void   start ();
    void   stop  ();
    void   update();
    void   connect(int port, std::string ip); //returns -1 on failure
    void   send(size_t target, uint8_t channel, std::unique_ptr< BinaryPackage >, bool reliable = true);

    size_t getChannelCount() { return _numberOfChannels; }
    int    getPort()         { return _port; }

    //config
    void setChannelCount          (uint8_t numberOfChannels);
    void setMaximumConnectionCount(size_t max);
    void setAcceptConnection      (bool accept);
    void setPort                  (int port);
    
    //config                     
    void setNewConnectionCallback    (                 std::function<void(size_t clientnumber, std::string ip, int port       )> func);
    void setConnectionFailedCallback (                 std::function<void(std::string name                                    )> func);
    void setDisconnectCallback       (                 std::function<void(size_t clientnumber                                 )> func);
    void setRecievedCallback         (uint8_t channel, std::function<void(size_t clientNumber, std::unique_ptr<BinaryPackage> )> func);


  private:
    void threadRun();

    ENetHost*   _connection             = nullptr;
    int         _numberOfConnections    = 1      ;
    uint8_t     _numberOfChannels       = 1      ;
    int         _port                   = 6112   ;
    bool        _acceptsConnections     = true   ;

    size_t      _clientNameCounter      = 0      ;
    
    std::function<void(size_t  clientNumber,std::string ip, int port)>                      _newConnection    ;
    std::function<void(std::string ip)>                                                     _connectionFailed ;
    std::function<void(size_t  clientNumber)>                                               _disconnect       ;
    std::vector<std::function<void(size_t  clientNumber, std::unique_ptr< BinaryPackage >)>> _recived         ;
    std::map<size_t, ENetPeer*>                                                             _peers            ;
    std::future<void>                                                                       _thread           ;
    moodycamel::ConcurrentQueue<NetReciveEvent>                                             _threadQueueRecive;
    moodycamel::ConcurrentQueue<NetSendEvent>                                               _threadQueueSend  ;

    static inline size_t numberOfConnectsions = 0;
  };
}