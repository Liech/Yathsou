#pragma once

#include "YolonaOss/OpenGL/Drawable.h"
#include "UyanahGameServer/Scene.h"

namespace Uyanah {
  class Client;
}

class ClientVisualization : public YolonaOss::GL::Drawable {
public:
  ClientVisualization(std::shared_ptr<Uyanah::Scene>& scene);
  virtual void load(YolonaOss::GL::DrawSpecification*) override;
  virtual void draw()                                  override;

private:
  std::shared_ptr<Uyanah::Scene>& _scene;
};