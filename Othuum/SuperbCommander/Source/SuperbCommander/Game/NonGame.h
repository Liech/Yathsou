#pragma once

#include <memory>
#include <nlohmann/json.hpp>

namespace Ahwassa {
  class Window;
  class DecalRenderer;
  class Decal;
}

namespace Superb {
  namespace Formation {
    class FormationDialog;
  }
  class NonGame {
  public:
    NonGame(Ahwassa::Window&);
    virtual ~NonGame() = default;

    void update();
    void menu();
    void preDraw();
    void draw();
    void start();
    void save(nlohmann::json&);
    void load(nlohmann::json&);

  private:
    Ahwassa::Window& _window;

    bool _dearIMGUIDemoWindow = false;
    float _fontScale = 1;

    std::unique_ptr<Formation::FormationDialog> _formationDialog;
    std::unique_ptr<Ahwassa::DecalRenderer>     _decalRenderer;
    std::shared_ptr<Ahwassa::Decal>             _decal;
  };
}