#pragma once

#include <functional>
#include "Keys.h"
struct GLFWwindow; 

#include "../Renderer/TextRenderer.h"
#include "../structs/Factory.h"

#define LaunchYolonaOss REGISTER(Drawable, TextRenderer, "TextRenderer", { "PreDrawCall" })

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
  void                       setCursorPos(std::pair<double, double>);
  float                      getMouseWheelMovement();

  int getWidth() { return _width; }
  int getHeight() { return _height; }

private:
  int _width  = 1920;
  int _height = 1080;
  GLFWwindow* _window = nullptr;
  float _mouseWheelMovement = 0;
};

