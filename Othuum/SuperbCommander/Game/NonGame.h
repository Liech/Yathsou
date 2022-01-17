#pragma once

#include <memory>
#include "AezeselFileIOLib/lib/json.hpp"

namespace Ahwassa {
  class Window;
}

namespace Superb {
  class FormationDialog;
  
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

    std::unique_ptr<FormationDialog> _formationDialog;
  };
}