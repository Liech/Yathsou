#pragma once

#include <memory>
#include <functional>
#include "IyathuumCoreLib/Singleton/Factory.h"
#include "IyathuumCoreLib/lib/glm/glm.hpp"

struct GLFWwindow;

namespace Ahwassa {
  class Drawable;
  class Input;

  class Window
  {
  public:
    Window(int width, int height);
    ~Window();

    Input& input();

    void run  ();
    void close();

    std::function<void()> Startup = []() {};
    std::function<void()> Update = []() {};

    int getWidth () { return _width; }
    int getHeight() { return _height; }

  private:
    int _width = 1920;
    int _height = 1080;
    GLFWwindow* _window = nullptr;
    std::unique_ptr<Input> _input;
  };
}
