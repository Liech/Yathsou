#include "../OpenGL/DrawSpecification.h"
#include "../Camera/Camera.h"
namespace YolonaOss {
  namespace GL {
    DrawSpecification::DrawSpecification(Window* w, std::shared_ptr<Camera::Camera> cam) {
      _window = w;
      _cam = cam;
    }
    std::shared_ptr<Camera::Camera> DrawSpecification::getCam() { return _cam; }

  }
}