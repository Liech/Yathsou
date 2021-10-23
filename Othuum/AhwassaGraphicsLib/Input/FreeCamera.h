#pragma once

#include "UIElement.h"
#include "IyathuumCoreLib/BaseTypes/Keys.h"

namespace Ahwassa {
  class Camera;
  class Input;

  class FreeCamera : public UIElement {
  public:
    FreeCamera(std::shared_ptr<Camera>, Input& inp, Iyathuum::Key);

    bool isFocus();
    void setFocus(bool focus);

    bool keyEvent(Iyathuum::Key button, Iyathuum::KeyStatus status) override;
    bool mouseEvent(glm::vec2 localPosition, Iyathuum::Key button, Iyathuum::KeyStatus status) override;
    bool mouseWheelEvent(glm::vec2 movement) override;
    bool mouseClickEvent(glm::vec2 localPosition, Iyathuum::Key button) override;
    bool mouseMoveEvent(glm::vec2 current, glm::vec2 movement) override;
    void update() override;
  private:

    bool                    _focus = false;
    std::shared_ptr<Camera> _camera;
    Input&                  _input;
    bool                    _wireframe = false;
    float                   _moveX = 0;
    float                   _moveY = 0;
    Iyathuum::Key           _toggleKey;
  };
}