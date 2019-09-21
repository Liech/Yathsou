#pragma once

#include <memory>
#include "glm/vec2.hpp"


namespace YolonaOss {
  namespace GL {
    class Window;
    class Camera;
  }
  class RTSCamera {
  public:
    RTSCamera(GL::Window* window);
    void load(std::shared_ptr<GL::Camera> camera);
    void update();

  private:
    GL::Window* _window;
    std::shared_ptr<GL::Camera> _camera;

    double                  _lastTime = 0;
  };
}