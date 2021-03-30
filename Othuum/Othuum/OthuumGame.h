#pragma once

#include <memory>

#include "VishalaNetworkLib/Protocoll/AuthoritarianGameClient.h"

class ClientControl;
class ClientVisualization;
namespace Uyanah {
  class Scene;
}
namespace Vishala {
  class AuthoritarianGameServer;
}
namespace Iyathuum {
  class UpdateTimer;
}

class OthuumGame {
public:
  OthuumGame();

  void tick();
  void update();

  void createServer(int port);

public:
  std::unique_ptr<Vishala::AuthoritarianGameClient<Uyanah::Scene>> _client ;
  std::shared_ptr<Uyanah::Scene>                                   _scene  ;
  std::shared_ptr<ClientControl>                                   _control;
  std::shared_ptr<ClientVisualization>                             _vis    ;
  std::unique_ptr<Iyathuum::UpdateTimer>                           _timer  ;
private:
  std::unique_ptr<Vishala::AuthoritarianGameServer>                _server;
};