#pragma once

#include "Protocoll.h"

namespace Vishala {
  //Lobby connector is the initial protocoll invoked to enter a lobby.
  //it asks the lobby for a port, generates a new connection to this port and invokes the next protocoll with the new connection  
  //connection should already has invoked start
  class LobbyConnector : public Protocoll {
  public:
    LobbyConnector(std::string ip, int port,std::shared_ptr<Protocoll> next,std::function<void(std::shared_ptr<Protocoll>)> nextProtocollInvoked, std::unique_ptr<Connection> connection);
    virtual void update() override;

    virtual std::string getName() { return "LobbyConnector"; }
  protected:
    virtual void messageRecived  (size_t player, size_t channel, std::unique_ptr<BinaryPackage> package) override;
    virtual void newConnection   (size_t clientnumber, std::string ip, int port                        ) override {}
    virtual void connectionFailed(std::string name                                                     ) override;
    virtual void disconnect      (size_t clientnumber                                                  ) override;
    virtual void initialization() override {  };

  private:
    void secondConnectionEstablished();

    bool                        _messageRecived   = false;
    std::unique_ptr<Connection> _secondConnection = nullptr;//connects to the real target, not only to the lobby main port
    std::shared_ptr<Protocoll>  _next;

    int         lobbyPort;
    std::string lobbyIP;
  };
}