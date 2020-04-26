#pragma once

#include "Protocoll.h"

namespace Vishala {

  //used by lobby to make one single client happy
  class LobbyChaperone : public Protocoll {
    enum class state {
      HeIsUnkown, HeIsKnown
    };
  public:
                 LobbyChaperone(std::string ip, int port, std::function<void(std::shared_ptr<Protocoll>)> nextProtocollInvoked, std::unique_ptr<Connection> connection);

    virtual std::string getName() { return "LobbyChaperone"; }

    virtual void messageRecived  (size_t player, size_t channel, std::unique_ptr<BinaryPackage> package) override;
    virtual void newConnection   (size_t clientnumber, std::string ip, int port                        ) override;
    virtual void connectionFailed(std::string name                                                     ) override;
    virtual void disconnect      (size_t clientnumber                                                  ) override;
    virtual void update          (                                                                     ) override;
    virtual void initialization() override {};
  private:
    bool          _connected = false;
    std::string   _ip               ;    
    LobbyChaperone::state _state = state::HeIsUnkown;
  };
}