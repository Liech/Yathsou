#pragma once

namespace Ahwassa {
  class Window;
}

namespace Superb {
  class FormationDialog {
  public:
    FormationDialog(Ahwassa::Window&);
    virtual ~FormationDialog() = default;

    void menu();

  private:
    void menuContent();

    Ahwassa::Window& _window;
  };
}