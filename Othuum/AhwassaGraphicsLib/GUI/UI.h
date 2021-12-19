#pragma once

namespace Ahwassa {
  class Window;

  class UI {
  public:
    UI(Ahwassa::Window*);

    void draw();
  private:

    bool show_demo_window = true;
    bool show_another_window = false;
  };
}