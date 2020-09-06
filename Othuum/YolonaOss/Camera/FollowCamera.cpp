#include "FollowCamera.h"
#include "Util/getPosition.h"

namespace YolonaOss
{
  namespace Camera
  {
    void FollowCamera::load(std::shared_ptr<YolonaOss::Camera::Camera> camera, GL::Window* window)
    {
      _camera = camera;
    }

    void FollowCamera::update()
    {
      glm::vec3 center = glm::vec3(0,0,0);
      for (auto target : _targets)
        center += target->getPosition();
      center /= _targets.size();

      _camera->setPosition(center + glm::vec3(4, 3, 3));
      _camera->setTarget(center);
    }

    void FollowCamera::setTarget(std::set<std::shared_ptr<GetPosition>> targets)
    {
      _targets = targets;
    }

  }
}