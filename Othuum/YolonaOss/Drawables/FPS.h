#pragma once

#include "../OpenGL/Drawable.h"
#include <chrono>


class FPS : public Drawable
{
public:
  FPS();
  ~FPS();

  // Inherited via Drawable
  virtual void load(DrawSpecification*) override;
  virtual void draw() override;

private:  
  std::chrono::time_point<std::chrono::steady_clock> _lastMeasurement;
  DrawSpecification*                                 _spec;
  double                                             _avFPS = 0;
};

