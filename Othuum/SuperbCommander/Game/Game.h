#pragma once

#include <memory>

namespace Ahwassa {
  class Window;
  class IMGUIRenderer;
}

namespace Superb {
  class Overlay;
  class Terrain;
  class Physic;
  class Database;

  class Game {
  public:
    Game(Ahwassa::Window&);
    virtual ~Game() = default;

    void update();
    void drawFirstLayer();
    void drawLastLayer();
    void drawMenu();

    Physic&   physic();
    Database& database();
  private:
    std::unique_ptr<Ahwassa::IMGUIRenderer> _ui;
    std::unique_ptr<Overlay>        _overlay ;
    std::unique_ptr<Terrain>        _terrain ;
    std::unique_ptr<Physic >        _physic  ;
    std::unique_ptr<Database>       _database;
  };
}