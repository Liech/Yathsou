#pragma once

#include <memory>
#include <functional>
#include "IyathuumCoreLib/lib/glm/glm.hpp"

struct GLFWwindow;

namespace Ahwassa {
  class Drawable;
  class Input;
  class Renderer;
  class Camera;

  class Window
  {
  public:
    Window(int width, int height);
    virtual ~Window();

    Input&                  input   ();
    Renderer&               renderer();
    std::shared_ptr<Camera> camera  ();

    void run  ();
    void close();
    void frame();

    std::function<void()> Startup = []() {};
    std::function<void()> Update  = []() {};

    int getWidth () { return _width; }
    int getHeight() { return _height; }

    GLFWwindow* ptr();
  private:
    int _width  = 1920;
    int _height = 1080;
    GLFWwindow* _window = nullptr;
    std::unique_ptr<Input>    _input;
    std::unique_ptr<Renderer> _renderer;
    std::shared_ptr<Camera>   _camera;
  };
}
