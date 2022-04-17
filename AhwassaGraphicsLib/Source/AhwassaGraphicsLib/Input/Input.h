#pragma once

#include <memory>
#include <map>
#include <vector>
#include <string>

#include <glm/glm.hpp>
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
    void                 resetCursorMovement(glm::vec2 v);

    void setFocus(UIElement* newFocus);
    UIElement* getCurrentFocus();

    void addUIElement(UIElement*);
    void addUIElement(UIElement*, size_t orderID);
    void removeUIElement(UIElement*);
    std::vector<UIElement*> getUIElements();

  //pseudo private:
    void update();
    void keyEvent  (Iyathuum::Key key, Iyathuum::KeyStatus status, int mode);
    void mouseEvent(Iyathuum::Key key, Iyathuum::KeyStatus status, int mode);
    void dropEvent(const std::string&);

  private:
    void mouseWheel(double x, double y);

    static Input* _instance;

    std::map<UIElement*, size_t> _uiElements;
    size_t                       _orderpos = 1000;

    GLFWwindow* _windowGL;
    Window*     _windowAhwassa;

    UIElement* _pressedWidget = nullptr;
    UIElement* _currentFocus  = nullptr;
    UIElement* _currentHover  = nullptr;
    glm::vec2  _oldMousePos;
    glm::vec2  _cursorpos;
  };
}