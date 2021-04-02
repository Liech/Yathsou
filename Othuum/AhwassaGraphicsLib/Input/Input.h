#pragma once

#include <memory>
#include <map>
#include <vector>

#include "IyathuumCoreLib/lib/glm/glm.hpp"
#include "IyathuumCoreLib/BaseTypes/Keys.h"

struct GLFWwindow;

namespace Ahwassa {
  class UIElement;
  class Window;

  class Input {
  public:
    static Input& instance();

    Input(GLFWwindow*, Window*);

    Iyathuum::KeyStatus  getKeyStatus(Iyathuum::Key key) const;
    void                 setCursorStatus(Iyathuum::CursorStatus);
    glm::vec2            getCursorPos() const;
    void                 setCursorPos(glm::vec2 pos);

    void setFocus(std::shared_ptr<UIElement> newFocus);
    std::shared_ptr<UIElement> getCurrentFocus();

    void addUIElement(std::shared_ptr<UIElement>);
    void removeUIElement(std::shared_ptr<UIElement>);
    std::vector<std::shared_ptr<UIElement>> getUIElements();

  //pseudo private:
    void update();
    void keyEvent  (Iyathuum::Key key, Iyathuum::KeyStatus status, int mode);
    void mouseEvent(Iyathuum::Key key, Iyathuum::KeyStatus status, int mode);

  private:
    void mouseWheel(double x, double y);

    static Input* _instance;

    std::map<std::shared_ptr<UIElement>, size_t> _uiElements;
    size_t                                       _orderpos = 0;

    GLFWwindow* _windowGL;
    Window*     _windowAhwassa;

    std::weak_ptr<UIElement> _pressedWidget;
    std::weak_ptr<UIElement> _currentFocus ;
    glm::vec2                _oldMousePos  ;
  };
}