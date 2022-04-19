#pragma once

#include "UIElement.h"
#include "IyathuumCoreLib/BaseTypes/Keys.h"

namespace Ahwassa {
  class Camera;
  class Input;

  class FreeCamera : public UIElement {
  public:
    FreeCamera(std::shared_ptr<Camera>, Input& inp, Iyathuum::Key);

    bool isFocus() const;
    void setFocus(bool focus);

    bool keyEvent(const Iyathuum::Key& button, const Iyathuum::KeyStatus& status) override;
    bool mouseEvent(const glm::vec2& localPosition, const Iyathuum::Key& button, const  Iyathuum::KeyStatus& status) override;
    bool mouseWheelEvent(const glm::vec2& movement) override;
    bool mouseClickEvent(const glm::vec2& localPosition, const Iyathuum::Key& button) override;
    bool mouseMoveEvent(const glm::vec2& current, const glm::vec2& movement) override;
    void update() override;
    virtual void endFocusEvent() override;
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