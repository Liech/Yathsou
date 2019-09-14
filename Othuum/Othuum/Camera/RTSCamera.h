#pragma once

#include <memory>
#include "YolonaOss/glm/vec2.hpp"
class Window;
class Camera;

class RTSCamera {
public:
  RTSCamera(Window* window);
  void load(std::shared_ptr<Camera> camera);
  void update();

private:
  Window*                 _window;
  std::shared_ptr<Camera> _camera;

  double                  _lastTime = 0;
};