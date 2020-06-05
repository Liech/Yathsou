#include "InputHandling.h"

#include "Drawables/Widgets/Widget.h"
#include "IyathuumCoreLib/Singleton/Database.h"
#include "Keys.h"

#include "YolonaOss/Util/Util.h"
#include "Window.h"
#include <GLFW/glfw3.h>

namespace YolonaOss {
  namespace GL {
    InputHandling& InputHandling::getInstance() {
      static InputHandling instance;
      return instance;
    }

    InputHandling::InputHandling() {
      _window        = nullptr;
      _yWindow       = nullptr;
      _pressedWidget = nullptr;
      _focusedWidget = nullptr;
    }

    YolonaOss::Widgets::Widget* InputHandling::getCurrentFocus() {
      return _focusedWidget;
    }

    void InputHandling::setFocus(YolonaOss::Widgets::Widget* newFocus) {
      if (newFocus == _focusedWidget)
        return;
      if (_focusedWidget)
        _focusedWidget->focusEnd();
      _focusedWidget = newFocus;
      if (_focusedWidget)
        _focusedWidget->focusStart();
    }

    void InputHandling::setWindow(GLFWwindow* window, YolonaOss::GL::Window* yWindow) {
      _window  = window ;
      _yWindow = yWindow;
    }

    void InputHandling::keyEvent(Key button, KeyStatus status, int mode) {
      std::set<Widgets::Widget*> inputWidgets = Iyathuum::Database<Widgets::Widget*>::getByTag("KeyboardInput");
      if (_focusedWidget != nullptr)
        _focusedWidget->focusedKeyboardInput(button, status);
      for (auto i : inputWidgets) 
        i->keyboardInput(button, status);
    }
    void InputHandling::mouseEvent(Key key, KeyStatus status, int mode) {
      double xpos, ypos;
      glfwGetCursorPos(_window, &xpos, &ypos);
      glm::vec2 mousePos((float)xpos, (float)(_yWindow->getHeight() - ypos));

      std::set<Widgets::Widget*> mouseStatusWidgets = Iyathuum::Database<Widgets::Widget*>::getByTag("MouseStatus");
      for (auto w : mouseStatusWidgets) {
        bool stop = w->mouseStatusChanged(mousePos - Util<2>::array2Vec(w->getGlobalPosition().getPosition()), key, status);
        if (stop)
          return;
      }
      bool hit = false;
      std::set<Widgets::Widget*> clickableWidgets = Iyathuum::Database<Widgets::Widget*>::getByTag("MouseClick");
      for (auto w : clickableWidgets) {
        bool insideParent = true;
        if (w->getParent() != nullptr)
          insideParent = w->getParent()->getGlobalPosition().isInside(Util<2>::vec2Array<double>(mousePos));
        if (w->getGlobalPosition().isInside(Util<2>::vec2Array<double>(mousePos)) && insideParent) {
          hit = true;
          if (status == KeyStatus::PRESS) {
            _pressedWidget = w;
            setFocus(w);
          }
          else
            if (status == KeyStatus::RELEASE && _pressedWidget == w) {
              bool stop = w->mouseClick(mousePos - Util<2>::array2Vec(w->getGlobalPosition().getPosition()), key);
              if (stop)
                return;
            }
        }
      }
      if (!hit)
        _focusedWidget = nullptr;
      std::set<std::function<bool(double, double)>*> functions = Iyathuum::Database<std::function<bool(double, double)>*>::getByTag("MouseClick");
      if (status == KeyStatus::PRESS) {
        for (auto f : functions) {
          bool stop = (*f)(xpos, ypos);
          if (stop)
            return;
        }
        std::set<std::function<bool(double, double)>> functions2 = Iyathuum::Database<std::function<bool(double, double)>>::getByTag("MouseClick");
        for (auto f : functions2) {
          bool stop = f(xpos, ypos);
          if (stop)
            return;
        }
      }
      if (status == KeyStatus::RELEASE)
        _pressedWidget = nullptr;
    }

    void InputHandling::updateEvent() {
      double xpos, ypos;
      glfwGetCursorPos(_window, &xpos, &ypos);
      glm::vec2 mousePos((float)xpos, (float)(_yWindow->getHeight() - ypos));
  
      if (mousePos != _oldMousePos) {
        std::set<Widgets::Widget*> moveWidgets = Iyathuum::Database<Widgets::Widget*>::getByTag("MouseMove");
        for (auto w : moveWidgets) {
          if (w->getPosition().isInside(Util<2>::vec2Array<double>(mousePos))) {
            w->mouseMove(mousePos - Util<2>::array2Vec(w->getPosition().getPosition()));
          }
        }
      }
      _oldMousePos = mousePos;
    }

  }
}