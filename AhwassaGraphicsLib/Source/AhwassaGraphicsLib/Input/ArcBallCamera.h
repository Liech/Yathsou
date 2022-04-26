#pragma once

#include "UIElement.h"
#include "IyathuumCoreLib/BaseTypes/Keys.h"

namespace Ahwassa {
  class Camera;
  class Input;

  class ArcBallCamera : public UIElement {
  public:
    ArcBallCamera(std::shared_ptr<Camera>, Input& inp);
    virtual ~ArcBallCamera() = default;

    bool keyEvent(const Iyathuum::Key& button, const Iyathuum::KeyStatus& status) override;
    bool mouseEvent(const glm::vec2& localPosition, const Iyathuum::Key& button, const Iyathuum::KeyStatus& status) override;
    bool mouseWheelEvent(const glm::vec2& movement) override;
    bool mouseClickEvent(const glm::vec2& localPosition, const Iyathuum::Key& button) override;
    bool mouseMoveEvent(const glm::vec2& current, const glm::vec2& movement) override;
    void update() override;
  private:
    void move(const glm::vec2& mouse, const glm::vec2& wheel, bool setCursor);

    glm::vec3               _lastTargetPosition;
    bool                    _arcAround = false;
    bool                    _panAround = false;
    std::shared_ptr<Camera> _camera;
    Input&                  _input;
  };
}