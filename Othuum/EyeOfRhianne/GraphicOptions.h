#pragma once

#include <memory>

namespace Ahwassa {
  class Window;
  class Button;
}

class GraphicOptions {
public:
  GraphicOptions(Ahwassa::Window* );

  void draw();

private:
  Ahwassa::Window* _window;
  std::shared_ptr<Ahwassa::Button> _showHide;
};