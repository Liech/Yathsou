#pragma once

#include "UIElement.h"
#include "IyathuumCoreLib/BaseTypes/Keys.h"

namespace Ahwassa {
  class Camera;
  class Input;

  class ArcBallCamera : public UIElement {
  public:
    ArcBallCamera(std::shared_ptr<Camera>, Input& inp, Iyathuum::Key);

    bool isFocus();
    void setFocus(bool focus);

    bool keyEvent(Iyathuum::Key button, Iyathuum::KeyStatus status) override;
    bool mouseEvent(glm::vec2 localPosition, Iyathuum::Key button, Iyathuum::KeyStatus status) override;
    bool mouseWheelEvent(glm::vec2 movement) override;
    bool mouseClickEvent(glm::vec2 localPosition, Iyathuum::Key button) override;
    bool mouseMoveEvent(glm::vec2 current, glm::vec2 movement) override;
    void update() override;
  private:
    void move(const glm::vec2& mouse, const glm::vec2& wheel, bool setCursor);

    glm::vec3               _lastTargetPosition;
    bool                    _focus = false;
    std::shared_ptr<Camera> _camera;
    Input&                  _input;
    Iyathuum::Key           _toggleKey;
  };
}