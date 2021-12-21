#pragma once

#include <memory>

namespace Athanah {
  class MapRenderer;
}

namespace Ahwassa {
  class IMesh;
  class Window;
}

namespace Superb {
  class Game;
  class UnitsVisualization;

  class Visualization {
  public:
    Visualization(Ahwassa::Window&, Game&);
    virtual ~Visualization() = default;

    void menu();
    void draw();
    void drawLastLayer();

  private:
    const Game&            _game;
    const Ahwassa::Window& _window;

    bool _drawTerrain = true;
    std::unique_ptr<Athanah::MapRenderer> _mapRenderer = nullptr;
    std::shared_ptr<Ahwassa::IMesh>       _mapMesh     = nullptr;

    bool _debugUnitView = true;
    bool _unitsView = true;
    std::unique_ptr<UnitsVisualization> _unitsVis;

  };
}