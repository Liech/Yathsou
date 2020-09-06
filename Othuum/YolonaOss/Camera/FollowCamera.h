#pragma once

#include <memory>
#include "IyathuumCoreLib/lib/glm/vec2.hpp"
#include "Camera.h"
#include "IyathuumCoreLib/Singleton/Factory.h"

namespace YolonaOss
{
  class GetPosition;

  namespace GL {
    class Window;
  }
  namespace Camera {
    class FollowCamera : public CameraMode
    {
      REGISTER(CameraMode, FollowCamera, "FollowCamera", { "Camera" })
    public:
      virtual void load(std::shared_ptr<YolonaOss::Camera::Camera> camera, GL::Window* window) override;
      virtual void update() override;

      static void setTarget(std::set<std::shared_ptr<GetPosition>>);

    private:
      std::shared_ptr<YolonaOss::Camera::Camera> _camera;
      static inline std::set<std::shared_ptr<GetPosition>>     _targets;
    };
  }
}