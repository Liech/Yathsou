#pragma once

#include "UIElement.h"

namespace Ahwassa {
  class Camera;
  class Input;

  class FreeCamera : public UIElement {
  public:
    FreeCamera(std::shared_ptr<Camera>, Input& inp);
    bool keyEvent(Iyathuum::Key button, Iyathuum::KeyStatus status) override;
    bool mouseWheelEvent(glm::vec2 movement) override;
    bool mouseClickEvent(glm::vec2 localPosition, Iyathuum::Key button) override;
    bool mouseMoveEvent(glm::vec2 movement) override;
    void startFocusEvent() {};
    void endFocusEvent  () {};
  private:
    bool _focus = false;
    std::shared_ptr<Camera> _camera;
    Input& _input;
  };
}