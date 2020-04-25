#pragma once

#include "Protocoll.h"

namespace Vishala {
  class EnterLobby_Server : public Protocoll {
  public:
                 EnterLobby_Server(std::function<void(std::shared_ptr<Protocoll>)> nextProtocollInvoked, std::unique_ptr<Connection> connection, std::string ip, int port);
    virtual void messageRecived  (size_t player, size_t channel, std::unique_ptr<BinaryPackage> package) override;
    virtual void newConnection   (size_t clientnumber, std::string ip, int port                        ) override;
    virtual void connectionFailed(std::string name                                                     ) override;
    virtual void disconnect      (size_t clientnumber                                                  ) override;
    virtual void update          (                                                                     ) override;
  };
}