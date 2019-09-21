#pragma once
namespace YolonaOss {
  namespace GL {
    class Window;
    class DrawSpecification
    {
    public:
      DrawSpecification(Window* w) {
        _window = w;
      }

      int width = 1920;
      int height = 1080;

      Window* getWindow() {
        return _window;
      }
    private:
      Window* _window;
    };
  }
}