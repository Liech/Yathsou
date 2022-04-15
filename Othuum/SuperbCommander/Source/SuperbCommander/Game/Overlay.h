#pragma once

#include <memory>
#include <nlohmann/json.hpp>

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
    void save(nlohmann::json&);
    void load(nlohmann::json&);
    void start();

  private:
    Ahwassa::Window& _window;

    std::unique_ptr<Ahwassa::FPS> _fps;
    bool                          _showFps = true;
  };
}