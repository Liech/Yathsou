#pragma once

#include "YolonaOss/OpenGL/Drawable.h"

namespace Uyanah {
  class Client;
}

class ClientVisualization : public YolonaOss::GL::Drawable {
public:
  void setClient(std::shared_ptr<Uyanah::Client> client);
  virtual void load(YolonaOss::GL::DrawSpecification*) override;
  virtual void draw()                                  override;

private:
  std::shared_ptr<Uyanah::Client> _client = nullptr;
};