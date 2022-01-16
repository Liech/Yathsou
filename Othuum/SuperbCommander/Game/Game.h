#pragma once

#include <memory>
#include "AezeselFileIOLib/lib/json.hpp"

namespace Ahwassa {
  class Window;
  class IMGUIRenderer;
}

namespace Superb {
  class Overlay;
  class Terrain;
  class Physic;
  class Database;
  class Units;
  class Visualization;
  class Control;
  class NonGame;

  class Game {
  public:
    Game(Ahwassa::Window&);
    virtual ~Game() = default;

    void update();
    void draw();
    void drawMenu();
    void save(nlohmann::json&);
    void load(nlohmann::json&);
    void start();

    Physic&   physic();
    Database& database();
    Terrain&  terrain();
    Units&    units();
    Overlay&  overlay();
  private:
    std::unique_ptr<Ahwassa::IMGUIRenderer> _ui;
    std::unique_ptr<Overlay>        _overlay      ;
    std::unique_ptr<Terrain>        _terrain      ;
    std::unique_ptr<Physic >        _physic       ;
    std::unique_ptr<Database>       _database     ;
    std::unique_ptr<Units   >       _units        ;
    std::unique_ptr<Visualization>  _visualization;
    std::unique_ptr<Control>        _control      ;
    std::unique_ptr<NonGame>        _nonGame      ; 
  };
}