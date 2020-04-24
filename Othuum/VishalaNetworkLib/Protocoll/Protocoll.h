#pragma once

#include "BinaryPackage.h"

#include <memory>
#include <functional>

namespace Vishala {
  class Connection;

  //Protocoll is a state in a state machine
  //Defines how to handle network Packages, somehwat a proxy for a connection, which can be replaced without changing the connection
  //In most cases this is a state machine too
  //decides upon invokation of next state
  class Protocoll {
  public:
                 Protocoll();
                 Protocoll(std::function<void(std::shared_ptr<Protocoll>)> nextProtocollInvoked, std::unique_ptr<Connection> connection);
            bool isActive();
    virtual void update();
  protected:
    virtual void messageRecived(size_t player, size_t channel, std::unique_ptr<BinaryPackage> package) = 0;
    virtual void newConnection(size_t clientnumber)                                                    = 0;
    virtual void connectionFailed(std::string name)                                                    = 0;
    virtual void disconnect(size_t clientnumber)                                                       = 0;

            void sendMessage(size_t player, size_t channel, std::unique_ptr<BinaryPackage> package);
            void connect(int port, std::string ip);
            void handOver(std::shared_ptr<Protocoll> next);
  private:
    void init(std::function<void(std::shared_ptr<Protocoll>)> nextProtocollInvoked, std::unique_ptr<Connection> connection);
    
    std::function<void(std::shared_ptr<Protocoll>)> _next;
    std::unique_ptr<Connection>                     _connection = nullptr;
  };
}