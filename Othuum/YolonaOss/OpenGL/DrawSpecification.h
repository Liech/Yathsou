#pragma once
class Window;

class DrawSpecification
{
public:
  DrawSpecification(Window* w) {
    _window = w;
  }

  int width;
  int height;

  Window* getWindow() {
    return _window;
  }
private:
  Window* _window;
};

