#pragma once

#include <functional>

class GLFWwindow;

class Window
{
public:
  Window(int width, int height);
  ~Window();

  void run();

  std::function<void()> Startup = []() {};
  std::function<void()> Update = []() {};

  GLFWwindow* getglwfWindow() { return _window; }

  double getTime();

private:
  int _width  = 1920;
  int _height = 1080;
  GLFWwindow* _window = nullptr;

};

