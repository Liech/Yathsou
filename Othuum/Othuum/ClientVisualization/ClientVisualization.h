#pragma once

#include "AhwassaGraphicsLib/Drawables/Drawable.h"
#include "UyanahGameServer/Scene.h"

namespace Uyanah {
  class Client;
}

class ClientVisualization : public Ahwassa::Drawable {
public:
  ClientVisualization(std::shared_ptr<Uyanah::Scene>& scene, Ahwassa::Window*);
  virtual void draw()                                  override;

private:
  std::shared_ptr<Uyanah::Scene>& _scene;
};