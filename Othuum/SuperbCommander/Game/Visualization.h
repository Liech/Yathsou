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

  class Visualization {
  public:
    Visualization(Ahwassa::Window&, Game&);
    virtual ~Visualization() = default;

    void menu();
    void draw();

  private:
    const Game&            _game;
    const Ahwassa::Window& _window;

    std::unique_ptr<Athanah::MapRenderer> _mapRenderer = nullptr;
    std::shared_ptr<Ahwassa::IMesh>       _mapMesh     = nullptr;
  };
}