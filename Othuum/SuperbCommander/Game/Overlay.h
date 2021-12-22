#pragma once

#include <memory>

namespace Ahwassa {
  class Window;
  class FPS;
  class Background;
}

namespace Superb {
  class Overlay {
  public:
    Overlay(Ahwassa::Window&);
    virtual ~Overlay() = default;

    void menu();
    void drawFirstLayer();
    void drawLastLayer();

  private:

    std::unique_ptr<Ahwassa::FPS>           _fps;
    bool showFPS = true;
  };
}