#pragma once

#include <memory>
#include "glm/vec2.hpp"
#include "Camera.h"
#include "../structs/Factory.h"


namespace YolonaOss {
  namespace GL {
    class Window;
    class Camera;
  }
  namespace Camera {
    class RTSCamera : public Camera {
      REGISTER(Camera,RTSCamera,"RTSCamera",{"Camera"})
    public:
      virtual void load(std::shared_ptr<GL::Camera> camera, GL::Window* window) override;
      virtual void update() override;

    private:
      GL::Window* _window;
      std::shared_ptr<GL::Camera> _camera;

      double                  _lastTime = 0;
    };
  }
}