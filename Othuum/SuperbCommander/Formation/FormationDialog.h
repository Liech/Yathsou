#pragma once

#include <memory>

namespace Ahwassa {
  class Window;
}

namespace Superb {
  class FormationWidget;

  class FormationDialog {
  public:
    FormationDialog(Ahwassa::Window&);
    virtual ~FormationDialog() = default;

    void menu();
    void preDraw();

  private:
    void menuContent();


    Ahwassa::Window& _window;   

    std::unique_ptr<FormationWidget> _canvas;
  };
}