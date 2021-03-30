#pragma once

#include <memory>

#include "VishalaNetworkLib/Protocoll/AuthoritarianGameClient.h"

namespace Uyanah {
  class Scene;
}

class OthuumGame {
public:
  OthuumGame();

public:
  std::unique_ptr<Vishala::AuthoritarianGameClient<Uyanah::Scene>> _client;
  std::shared_ptr<Uyanah::Scene> _scene;

};