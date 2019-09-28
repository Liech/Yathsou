#pragma once
#include <memory>
#include "../Camera/Camera.h"
namespace YolonaOss {
  namespace GL {
    class Window;
    class DrawSpecification
    {
    public:
      DrawSpecification(Window* w, std::shared_ptr<YolonaOss::Camera::Camera> cam);

      int width = 1920;
      int height = 1080;

      std::shared_ptr<YolonaOss::Camera::Camera> getCam();
      Window* getWindow()                  { return _window; }
    private:
      Window* _window;
      std::shared_ptr<YolonaOss::Camera::Camera> _cam;
    };
  }
}