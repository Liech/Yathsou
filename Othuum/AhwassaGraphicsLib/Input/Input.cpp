#include "Input.h"

#include "YolonaOss/Lib/glad/include/glad/glad.h"
#include "YolonaOss/Lib/GLWF/include/GLFW/glfw3.h"

#include "UIElement.h"
#include "Window.h"

namespace Ahwassa {
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
  void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);


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
    glfwSetMouseButtonCallback(_windowGL, mouse_button_callback);
    glfwSetKeyCallback(_windowGL, key_callback);
    glfwSetScrollCallback(_windowGL, [](GLFWwindow* window, double xoffset, double yoffset)
    {
      Input::instance().mouseWheel(xoffset, yoffset);
    });
  }

  Iyathuum::KeyStatus Input::getKeyStatus(Iyathuum::Key key) const{
    if ((int)key <= 7)
      return (Iyathuum::KeyStatus)((int)glfwGetMouseButton(_windowGL, (int)key));
    else
      return (Iyathuum::KeyStatus)((int)glfwGetKey(_windowGL, (int)key));
  }

  void Input::setCursorStatus(Iyathuum::CursorStatus status) {
    glfwSetInputMode(_windowGL, GLFW_CURSOR, (int)status);
  }

  glm::vec2 Input::getCursorPos() const {
    double xpos, ypos;
    glfwGetCursorPos(_windowGL, &xpos, &ypos);
    return glm::vec2(xpos, _windowAhwassa->getHeight() - ypos);
  }

  void Input::setCursorPos(glm::vec2 cursorPos) {
    glfwSetCursorPos(_windowGL, cursorPos.x, cursorPos.y);
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

  void Input::setFocus(std::shared_ptr<UIElement> newFocus) {
    auto current = _currentFocus.lock();
    if (newFocus == current)
      return;
    if (current)
      current->endFocusEvent();
    _currentFocus = newFocus;
    if (newFocus)
      newFocus->startFocusEvent();
  }

  std::shared_ptr<UIElement> Input::getCurrentFocus() {
    return _currentFocus.lock();
  }

  void Input::keyEvent(Iyathuum::Key button, Iyathuum::KeyStatus status, int mode) {
    auto focus = _currentFocus.lock();
    if (focus)
      if (focus->focusKeyEvent(button, status))
        return;
    auto inputWidgets = getUIElements();
    for (auto i : inputWidgets)
      if (i->keyEvent(button, status))
        return;
  }

  void Input::mouseEvent(Iyathuum::Key key, Iyathuum::KeyStatus status, int mode) {
    glm::vec2 mousePos = getCursorPos();

    auto inputWidgets = getUIElements();

    for (auto w : inputWidgets) {
      bool stop = w->mouseEvent(mousePos - w->getGlobalPosition().getPosition(), key, status);
      if (stop)
        return;
    }

    bool hit = false;
    for (auto w : inputWidgets) {
      if (w->getGlobalPosition().isInside(mousePos)) {
        hit = true;
        if (status == Iyathuum::KeyStatus::PRESS) {
          _pressedWidget = w;
          setFocus(w);
        }
        else {
          auto pressedWidget = _pressedWidget.lock();
          if (status == Iyathuum::KeyStatus::RELEASE && pressedWidget == w) {
            bool stop = w->mouseClickEvent(mousePos - w->getGlobalPosition().getPosition(), key);
            if (stop)
              return;
          }
        }
      }
    }
    if (!hit)
      _currentFocus = std::weak_ptr<UIElement>();
    if (status == Iyathuum::KeyStatus::RELEASE)
      _pressedWidget = std::weak_ptr<UIElement>();
  }

  void Input::mouseWheel(double x, double y) {
    auto inputWidgets = getUIElements();

    auto c = getCursorPos();
    for (auto w : inputWidgets) {
      if (!w->getGlobalPosition().isInside(c))
        continue;
      bool stop = w->mouseWheelEvent(glm::vec2(x, y));
      if (stop) return;
    }
  }

  void Input::update() {
    glm::vec2 mousePos = getCursorPos();

    if (mousePos != _oldMousePos) {
      auto inputWidgets = getUIElements();
      for (auto w : inputWidgets) {
        if (w->getGlobalPosition().isInside(mousePos)) {
          w->mouseMoveEvent(mousePos - w->getGlobalPosition().getPosition());
        }
      }
    }
    _oldMousePos = mousePos;
  }

  void Input::addUIElement(std::shared_ptr<UIElement> elem) {
    _uiElements[elem] = _orderpos;
    _orderpos++;
  }

  void Input::removeUIElement(std::shared_ptr<UIElement> elem) {
    _uiElements.erase(elem);
  }

  std::vector<std::shared_ptr<UIElement>> Input::getUIElements() {
    struct compare {
      bool operator()(std::pair<std::shared_ptr<UIElement>, size_t> const& left,
        std::pair<std::shared_ptr<UIElement>, size_t> const& right) const {
        return left.first > right.first; //reverse!
      }
    };

    std::vector<std::pair<std::shared_ptr<UIElement>, size_t> > sortList(_uiElements.begin(), _uiElements.end());
    std::sort(sortList.begin(), sortList.end(), compare());
    std::vector<std::shared_ptr<UIElement>> result;
    result.resize(sortList.size());
    for (size_t i = 0; i < sortList.size(); i++)
      result[i] = sortList[i].first;
    return result;
  }
}