#pragma once

#include <memory>

#include "Keys.h"
#include "glm/glm.hpp"
#include "glad/glad.h"
//#include <GLFW/glfw3.h>

struct GLFWwindow;

namespace YolonaOss {
  namespace Widgets {
    class Widget;
  }
  namespace GL {
    class Window;

    class InputHandling {
    public:
      static InputHandling& getInstance();

      void setWindow(GLFWwindow* window, YolonaOss::GL::Window* yWindow);
      
      void setFocus(YolonaOss::Widgets::Widget* newFocus);
      YolonaOss::Widgets::Widget* getCurrentFocus();

      void mouseWheel(double x, double y);
      void keyEvent(Key key, KeyStatus status, int mode);
      void mouseEvent(Key key, KeyStatus status, int mode);
      void updateEvent();
      
    private:
      InputHandling();

      glm::vec2                   _oldMousePos = glm::vec2();
      GLFWwindow*                 _window                   ;
      YolonaOss::GL::Window*      _yWindow                  ;
      YolonaOss::Widgets::Widget* _pressedWidget;
      YolonaOss::Widgets::Widget* _focusedWidget;
    };
  }
}