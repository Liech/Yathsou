#pragma once

#include <memory>
#include <functional>

#include "VishalaNetworkLib/Protocoll/AuthoritarianGameServer.h"
#include "VishalaNetworkLib/Protocoll/AuthoritarianGameClient.h"
#include "VishalaNetworkLib/Protocoll/LiberalGameClient.h"
#include "VishalaNetworkLib/Protocoll/LiberalGameServer.h"

class ClientControl;
class ClientVisualization;
namespace Uyanah {
  class Scene;
}
namespace Vishala {
  class AuthoritarianGameServer;
  class LiberalGameServer;
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
  OthuumGame(bool authoritarian = true);

  void load(YolonaOss::GL::DrawSpecification* spec);
  
  void tick();
  void update();
  void draw();

  void createServer(int port);
  void createClient(int myPort, int serverPort, std::string ip);

private:
  bool _authoritarian = false;
  int  _fps = 60;

  std::unique_ptr<Vishala::AuthoritarianGameClient<Uyanah::Scene>> _authoClient;
  std::unique_ptr<Vishala::AuthoritarianGameServer>                _authoServer;
  std::unique_ptr<Vishala::LiberalGameClient      <Uyanah::Scene>> _libClient  ;
  std::unique_ptr<Vishala::LiberalGameServer      >                _libServer  ;

  std::shared_ptr<Uyanah::Scene>                                   _scene    ;
  std::shared_ptr<ClientControl>                                   _control  ;
  std::unique_ptr<Iyathuum::UpdateTimer>                           _timer    ;
  std::shared_ptr<YolonaOss::GL::DrawableList>                     _drawables;
  std::shared_ptr<ClientVisualization>                             _vis      ;
};