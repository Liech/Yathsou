#pragma once
#include <memory>
#include "IyathuumCoreLib/lib/glm/vec2.hpp"
#include "Camera.h"
#include "IyathuumCoreLib/Singleton/Factory.h"
namespace YolonaOss {
  namespace GL {
    class Window;
    class Camera;
  }
  namespace Camera {
    class Camera2D : public CameraMode {
      REGISTER(CameraMode, Camera2D, "Camera2D", { "Camera" })
    public:
      virtual void load(std::shared_ptr<YolonaOss::Camera::Camera> camera, GL::Window* window) override;
      virtual void update() override;

    private:
      GL::Window* _window;
      std::shared_ptr<YolonaOss::Camera::Camera> _camera;

      float _ortho = 1;
      double                  _lastTime = 0;
      glm::vec2               _lastCursorPos;
    };
  }
}