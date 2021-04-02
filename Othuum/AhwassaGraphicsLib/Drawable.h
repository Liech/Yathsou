#pragma once

namespace Ahwassa {
  class Window;

  class Drawable
  {
  public:
    Drawable(Window*);
    virtual ~Drawable() {}

    virtual void draw() = 0;
    virtual void debugDraw() {};

  protected:
    Window* getWindow();
  private:
    Window* _window;
  };
}