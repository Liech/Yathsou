#pragma once

#include "../OpenGL/Drawable.h"
#include <chrono>


namespace YolonaOss {
  class FPS : public GL::Drawable
  {
  public:
    FPS();
    ~FPS();

    // Inherited via Drawable
    virtual void load(GL::DrawSpecification*) override;
    virtual void draw() override;

  private:
    std::chrono::time_point<std::chrono::steady_clock> _lastMeasurement;
    GL::DrawSpecification*                             _spec;
    double                                             _avFPS = 0;
  };
}
