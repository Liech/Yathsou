#pragma once

#include <functional>
#include "Keys.h"
struct GLFWwindow;

class Window
{
public:
  Window(int width, int height);
  ~Window();

  void run();

  std::function<void()> Startup = []() {};
  std::function<void()> Update = []() {};

  KeyStatus                  getKeyStatus(KeyboardKey key);
  double                     getTime();
  void                       setCursorStatus(CursorStatus);
  std::pair<double, double>  getCursorPos();
  std::pair<double, double>  getCursorMovement();
  void                       setCatchCursor(bool Catch);

private:
  int _width  = 1920;
  int _height = 1080;
  GLFWwindow* _window = nullptr;
  bool _catchCursor = false;
  std::pair<double, double> _lastCursorPos;
  std::pair<double, double> _cursorMovement;
};

