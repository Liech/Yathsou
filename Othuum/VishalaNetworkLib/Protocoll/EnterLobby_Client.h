#pragma once

#include "Protocoll.h"

namespace Vishala {
  class EnterLobby_Client : public Protocoll {
    // Inherited via Protocoll
    virtual void messageRecived  (size_t player, size_t channel, std::unique_ptr<BinaryPackage> package) override;
    virtual void newConnection   (size_t clientnumber                                                  ) override;
    virtual void connectionFailed(std::string name                                                     ) override;
    virtual void disconnect      (size_t clientnumber                                                  ) override;
    virtual void update          (                                                                     ) override;
  };
}