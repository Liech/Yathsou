#pragma once

#include <memory>
#include "AezeselFileIOLib/lib/json.hpp"

namespace Ahwassa {
  class Window;
}

namespace Superb {
  namespace Formation {
    class FormationDialog;
  }
  class NonGame {
  public:
    NonGame(Ahwassa::Window&);
    virtual ~NonGame() = default;

    void menu();
    void preDraw();
    void start();
    void save(nlohmann::json&);
    void load(nlohmann::json&);

  private:
    Ahwassa::Window& _window;

    bool _dearIMGUIDemoWindow = false;
    float _fontScale = 1;

    std::unique_ptr<Formation::FormationDialog> _formationDialog;
  };
}