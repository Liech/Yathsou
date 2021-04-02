#pragma once

#include <memory>
#include <functional>
#include "IyathuumCoreLib/BaseTypes/Keys.h"
#include "IyathuumCoreLib/Singleton/Factory.h"
#include "IyathuumCoreLib/lib/glm/glm.hpp"

struct GLFWwindow;

namespace Ahwassa {
  class Window
  {
  public:
    Window(int width, int height);
    ~Window();

    void run();
    void close();

    std::function<void()> Startup = []() {};
    std::function<void()> Update = []() {};

    Iyathuum::KeyStatus  getKeyStatus(Iyathuum::Key key);
    double     getTime();
    void       setCursorStatus(Iyathuum::CursorStatus);
    glm::vec2  getCursorPos();
    void       setCursorPos(glm::vec2 pos);

    int getWidth() { return _width; }
    int getHeight() { return _height; }

  private:

    int _width = 1920;
    int _height = 1080;
    GLFWwindow* _window = nullptr;
  };
}
