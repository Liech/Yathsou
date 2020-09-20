#pragma once

#include <memory>
#include <functional>
#include "Keys.h"
struct GLFWwindow; 

#include "../Renderer/TextRenderer.h"
#include "IyathuumCoreLib/Singleton/Factory.h"

namespace YolonaOss {
  namespace GL {
    class Window
    {
    public:
      Window(int width, int height);
      ~Window();

      void run();
      void close();

      std::function<void()> Startup = []() {};
      std::function<void()> Update = []() {};

      DrawSpecification* getSpec() { return _spec; }

      KeyStatus  getKeyStatus(Key key);
      double     getTime();
      void       setCursorStatus(CursorStatus);
      glm::vec2  getCursorPos();
      void       setCursorPos(glm::vec2 pos);
      float      getMouseWheelMovement();

      int getWidth() { return _width; }
      int getHeight() { return _height; }

    private:

      int _width = 1920;
      int _height = 1080;
      GLFWwindow* _window = nullptr;
      float _mouseWheelMovement = 0;
      DrawSpecification* _spec;
    };
  }
}
