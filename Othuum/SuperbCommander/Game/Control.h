#pragma once

#include <memory>
#include "AezeselFileIOLib/lib/json.hpp"

namespace Ahwassa {
  class Window;
  class FreeCamera;
  class ArcBallCamera;
}

namespace Superb {
  class Game;
  class DriveInterface;
  class NavigationUI;

  class Control {
  public:
    Control(Ahwassa::Window&, Game&);
    virtual ~Control() = default;

    void menu();
    void update();
    void debugDraw();
    void save(nlohmann::json&);
    void load(nlohmann::json&);
    void start();

    Ahwassa::ArcBallCamera& arcCamera();
  private:
    Game&            _game;
    Ahwassa::Window& _window;

    std::unique_ptr<Ahwassa::FreeCamera>    _freeCam;
    std::unique_ptr<Ahwassa::ArcBallCamera> _arcCam;
    std::unique_ptr<Superb::DriveInterface> _driveUI;
    std::unique_ptr<Superb::NavigationUI>   _navUI;

    bool _navUIDebugDraw = true;
  };
}