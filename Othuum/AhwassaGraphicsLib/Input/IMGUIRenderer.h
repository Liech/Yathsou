#pragma once

namespace Ahwassa {
  class Window;

  class IMGUIRenderer {
  public:
    IMGUIRenderer(Ahwassa::Window*);
    void start();
    void end();
  };
}