#include "Input.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "UIElement.h"
#include "AhwassaGraphicsLib/Core/Window.h"

namespace Ahwassa {
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
  void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
  void drop_callback(GLFWwindow* window, int count, const char** paths);


  Input* Input::_instance = nullptr;
  Input& Input::instance() {
    assert(_instance != 0);
    return *_instance;
  }

  Input::Input(GLFWwindow* win, Window* winAw) {
    _windowGL      = win;
    _windowAhwassa = winAw;
    _instance      = this;

    // Set the required callback functions

    glfwSetDropCallback(_windowGL, drop_callback);
    glfwSetMouseButtonCallback(_windowGL, mouse_button_callback);
    glfwSetKeyCallback(_windowGL, key_callback);
    glfwSetScrollCallback(_windowGL, [](GLFWwindow* window, double xoffset, double yoffset)
    {
      Input::instance().mouseWheel(xoffset, yoffset);
    });
  }

  Iyathuum::KeyStatus Input::getKeyStatus(const Iyathuum::Key& key) const{
    if ((int)key <= 7)
      return (Iyathuum::KeyStatus)((int)glfwGetMouseButton(_windowGL, (int)key));
    else
      return (Iyathuum::KeyStatus)((int)glfwGetKey(_windowGL, (int)key));
  }

  void Input::setCursorStatus(const Iyathuum::CursorStatus& status) {
    glfwSetInputMode(_windowGL, GLFW_CURSOR, (int)status);
  }

  glm::vec2 Input::getCursorPos() const {
    double xpos, ypos;
    glfwGetCursorPos(_windowGL, &xpos, &ypos);
    return glm::vec2(xpos, _windowAhwassa->getResolution()[1] - ypos);
  }

  void Input::setCursorPos(const glm::vec2& cursorPos) {
    glfwSetCursorPos(_windowGL, cursorPos.x, cursorPos.y);
    _cursorpos = cursorPos;
  }


  void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
  {
    Input::instance().mouseEvent((Iyathuum::Key)button, (Iyathuum::KeyStatus)action, mods);
  }

  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
  {
    Input::instance().keyEvent((Iyathuum::Key)key, (Iyathuum::KeyStatus)action, mode);
    if ((int)key == GLFW_KEY_ESCAPE && (int)action == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);
  }

  void Input::setFocus(UIElement* newFocus) {
    if (newFocus == _currentFocus)
      return;
    if (_currentFocus)
      _currentFocus->endFocusEvent();
    _currentFocus = newFocus;
    if (newFocus)
      newFocus->startFocusEvent();
  }

  UIElement* Input::getCurrentFocus() const {
    return _currentFocus;;
  }

  void Input::keyEvent(Iyathuum::Key button, Iyathuum::KeyStatus status, int mode) {
    if (_currentFocus)
      if (_currentFocus->focusKeyEvent(button, status))
        return;
    auto inputWidgets = getUIElements();
    for (auto i : inputWidgets)
      if (i->keyEvent(button, status))
        return;
  }


  void Input::mouseEvent(Iyathuum::Key key, Iyathuum::KeyStatus status, int mode) {
    glm::vec2 mousePos = getCursorPos();

    auto inputWidgets = getUIElements();

    bool hit = false;
    for (auto w : inputWidgets) {
      bool eventStop = w->mouseEvent(mousePos - w->getGlobalPosition().getPosition(), key, status);
      if (eventStop)
        return;
      if (w->isInside(mousePos,Iyathuum::Key::KEY_NONE)) {
        hit = true;
        if (status == Iyathuum::KeyStatus::PRESS) {
          _pressedWidget = w;
          setFocus(w);
          return;
        }
        else {
          if (status == Iyathuum::KeyStatus::RELEASE && _pressedWidget == w) {
            bool stop = w->mouseClickEvent(mousePos - w->getGlobalPosition().getPosition(), key);
            if (stop)
              return;
          }
        }
      }
    }
    if (!hit) {
      _currentFocus = nullptr;
    }
    if (status == Iyathuum::KeyStatus::RELEASE)
      _pressedWidget = nullptr;
  }

  void Input::mouseWheel(double x, double y) {
    auto inputWidgets = getUIElements();

    auto c = getCursorPos();
    for (auto w : inputWidgets) {
      if (!w->isInside(c, Iyathuum::Key::KEY_WHEEL))
        continue;
      bool stop = w->mouseWheelEvent(glm::vec2(x, y));
      if (stop) return;
    }
  }

  void Input::update() {
    _cursorpos = getCursorPos();

    auto inputWidgets = getUIElements();

    if (_currentHover && !_currentHover->isInside(_cursorpos, Iyathuum::Key::KEY_NONE)) {
      _currentHover->mouseLeaveEvent();
      _currentHover = nullptr;
    }

    for (auto w : inputWidgets) {
      if (w->isInside(_cursorpos, Iyathuum::Key::KEY_NONE)) {
        if (_currentFocus == w)
          break;
        if (_currentFocus != nullptr)
          _currentFocus->mouseLeaveEvent();
        _currentHover = w;
        w->mouseEnterEvent();
        break;
      }
    }

    if (_cursorpos != _oldMousePos) {
      for (auto w : inputWidgets) {
        if (w->isInside(_cursorpos, Iyathuum::Key::KEY_NONE)) {
          if (w->mouseMoveEvent(_cursorpos - w->getGlobalPosition().getPosition(), _cursorpos - _oldMousePos))
            break;
        }
      }
    }
    for (auto w : inputWidgets)
      w->update();

    _oldMousePos = _cursorpos;
  }

  void Input::resetCursorMovement(const glm::vec2& v) {
    _oldMousePos = v;
  }

  void Input::addUIElement(UIElement* elem) {
    _uiElements[elem] = _orderpos;
    _orderpos++;
  }

  void Input::addUIElement(UIElement* elem, size_t orderID) {
    _uiElements[elem] = orderID;
  }

  void Input::removeUIElement(UIElement* elem) {
    _uiElements.erase(elem);
  }

  std::vector<UIElement*> Input::getUIElements() const {
    struct compare {
      bool operator()(std::pair<UIElement*, size_t> const& left,
        std::pair<UIElement*, size_t> const& right) const {
        return left.second > right.second; //reverse!
      }
    };

    std::vector<std::pair<UIElement*, size_t> > sortList(_uiElements.begin(), _uiElements.end());
    std::sort(sortList.begin(), sortList.end(), compare());
    std::vector<UIElement*> result;
    result.resize(sortList.size());
    size_t used = 0;
    for (size_t i = 0; i < sortList.size(); i++) {
      if (!sortList[i].first->isVisible())
        continue;
      result[used] = sortList[i].first;
      used++;
    }
    result.resize(used);
    return result;
  }

  void Input::dropEvent(const std::string& path) {
    auto inputWidgets = getUIElements();
    for (auto w : inputWidgets) {
      if (w->isInside(_cursorpos, Iyathuum::Key::KEY_DROP)) {
        if (w->dropEvent(path))
          break;
      }
    }
  }

  void drop_callback(GLFWwindow* window, int count, const char** paths)
  {
    int i;
    for (i = 0; i < count; i++)
      Input::instance().dropEvent(std::string(paths[i]));
    
  }
}