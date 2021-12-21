#pragma once

#include <memory>

namespace Ahwassa {
  class Window;
  class IMGUIRenderer;
}

namespace Superb {
  class OverlayMenu;

  class MainMenu {
  public:
    MainMenu(Ahwassa::Window&);
    virtual ~MainMenu() = default;

    void drawFirstLayer();
    void drawLastLayer();
    void drawMenu();
  private:
    std::unique_ptr<Ahwassa::IMGUIRenderer> ui;
    std::unique_ptr<Superb::OverlayMenu>    overlay;
  };
}