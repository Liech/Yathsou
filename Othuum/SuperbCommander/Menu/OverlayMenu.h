#pragma once

#include <memory>
#include "IyathuumCoreLib/lib/glm/glm.hpp"

namespace Ahwassa {
  class Window;
  class FPS;
  class Background;
}

namespace Superb {
  class OverlayMenu {
  public:
    OverlayMenu(Ahwassa::Window&);
    virtual ~OverlayMenu() = default;

    void menu();
    void drawFirstLayer();
    void drawLastLayer();
  private:

    std::unique_ptr<Ahwassa::Background> background;
    glm::vec3                            backgroundColor = glm::vec3(0.2f,0.3f,0.3f);

    std::unique_ptr<Ahwassa::FPS>        fps;
    bool showFPS = true;
  };
}