#pragma once

#include "Units.h"

namespace Superb {
  class UnitsVisualization {
  public:
    UnitsVisualization(Ahwassa::Window*, Units&);

    void draw();
    void debugDraw();
  private:

    Ahwassa::Window* _window;
    Units&           _units;
  };
}