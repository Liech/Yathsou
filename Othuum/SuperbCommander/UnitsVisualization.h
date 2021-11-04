#pragma once

#include "Units.h"

namespace Athanah {
  class SupComModelFactory;
}

namespace Superb {
  class UnitsVisualization {
  public:
    UnitsVisualization(Ahwassa::Window*, Units&);

    void draw();
    void debugDraw();
  private:

    std::shared_ptr<Athanah::SupComModelFactory> _models;

    Ahwassa::Window* _window;
    Units&           _units;
  };
}