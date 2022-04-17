#pragma once

#include "AhwassaGraphicsLib/Drawables/Drawable.h"
#include <chrono>

namespace Ahwassa {
  class BasicTextRenderer;

  class FPS : public Drawable
  {
  public:
    FPS( Window*);
    ~FPS();

    virtual void draw() override;

  private:
    std::chrono::time_point<std::chrono::steady_clock> _lastMeasurement;
    double                                             _avFPS = 0;  
    std::unique_ptr< BasicTextRenderer>                _renderer;
  };
}
