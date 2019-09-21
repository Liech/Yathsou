#pragma once

namespace YolonaOss {
  namespace GL {
    class Camera;
    class Window;
  }
  namespace Camera {
    class Camera {
    public:
      virtual void load(std::shared_ptr<GL::Camera> camera, GL::Window* window) = 0;
      virtual void update() = 0;
    };
  }
}