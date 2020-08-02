#pragma once

#include <memory>
#include "IyathuumCoreLib/lib/glm/vec2.hpp"
#include "Camera.h"
#include "IyathuumCoreLib/Singleton/Factory.h"


namespace YolonaOss {
  namespace GL {
    class Window;
  }
  namespace Camera {
    class RTSCamera : public CameraMode {
      REGISTER(CameraMode,RTSCamera,"RTSCamera",{"Camera"})
    public:
      virtual void load(std::shared_ptr<YolonaOss::Camera::Camera> camera, GL::Window* window) override;
      virtual void update() override;

    private:
      GL::Window* _window;
      std::shared_ptr<YolonaOss::Camera::Camera> _camera;

      double                  _lastTime = 0;
    };
  }
}