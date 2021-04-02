#pragma once
#include <memory>


namespace Ahwassa {
    class Window;

    class DrawSpecification
    {
    public:
      DrawSpecification(Window* w);

      int width = 1920;
      int height = 1080;

      Window* getWindow()                  { return _window; }
    private:
      Window* _window;
    };
}