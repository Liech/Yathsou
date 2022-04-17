#pragma once

namespace Ahwassa {
  class Window;

  class IMGUIRenderer {
  public:
    IMGUIRenderer(Ahwassa::Window*);
    virtual ~IMGUIRenderer();

    void start();
    void end();
  };
}