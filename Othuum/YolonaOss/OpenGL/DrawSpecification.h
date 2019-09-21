#pragma once
#include <memory>

namespace YolonaOss {
  namespace GL {
    class Window;
    class Camera;
    class DrawSpecification
    {
    public:
      DrawSpecification(Window* w, std::shared_ptr<Camera> cam);

      int width = 1920;
      int height = 1080;

      std::shared_ptr<Camera> getCam();
      Window* getWindow()                  { return _window; }
    private:
      Window* _window;
      std::shared_ptr<Camera> _cam;
    };
  }
}