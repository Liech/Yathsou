#include "Drawable.h"

namespace Ahwassa {
  Drawable::Drawable(Window* win) {
    _window = win;
  }

  Window* Drawable::getWindow() {
    return _window;
  }
}

