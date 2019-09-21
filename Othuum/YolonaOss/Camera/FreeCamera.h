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
    class FreeCamera : public Camera {
      REGISTER(Camera, FreeCamera, "FreeCamera", {"Camera"})
    public:
      virtual void load(std::shared_ptr<GL::Camera> camera, GL::Window* window) override;
      virtual void update() override;

    private:
      GL::Window* _window;
      std::shared_ptr<GL::Camera> _camera;

      double                  _lastTime = 0;
      glm::vec2               _lastCursorPos;
    };
  }
}