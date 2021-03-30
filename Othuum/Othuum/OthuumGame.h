#pragma once

#include <memory>
#include <functional>

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
namespace YolonaOss {
  namespace GL {
    class DrawableList;
    class DrawSpecification;
  }
}

class OthuumGame {
public:
  OthuumGame();

  void load(YolonaOss::GL::DrawSpecification* spec);
  
  void tick();
  void update();
  void draw();

  void createServer(int port);
  void createClient(int myPort, int serverPort, std::string ip);

private:
  std::unique_ptr<Vishala::AuthoritarianGameClient<Uyanah::Scene>> _client   ;
  std::shared_ptr<Uyanah::Scene>                                   _scene    ;
  std::shared_ptr<ClientControl>                                   _control  ;
  std::unique_ptr<Iyathuum::UpdateTimer>                           _timer    ;
  std::shared_ptr<YolonaOss::GL::DrawableList>                     _drawables;
  std::shared_ptr<ClientVisualization>                             _vis      ;
  std::unique_ptr<Vishala::AuthoritarianGameServer>                _server   ;
};