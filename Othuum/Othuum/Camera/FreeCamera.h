#pragma once
#include <memory>

class Window;
class Camera;

class FreeCamera {
public:
  FreeCamera(Window* window);
  void load(std::shared_ptr<Camera> camera);
  void update();

private:
  Window*                 _window;
  std::shared_ptr<Camera> _camera;

  double                  _lastTime = 0;
};