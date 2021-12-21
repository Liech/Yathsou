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
    Visualization(const Ahwassa::Window&, const Game&);
    virtual ~Visualization() = default;

    void menu();
    void draw();

  private:
    void gather();

  private:
    const Game&            _game;
    const Ahwassa::Window& _window;

    std::unique_ptr<Athanah::MapRenderer> _mapRenderer = nullptr;
    std::shared_ptr<Ahwassa::IMesh>       _mapMesh     = nullptr;
  };
}