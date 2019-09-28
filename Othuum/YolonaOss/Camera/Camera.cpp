#include "Camera.h"

namespace YolonaOss {
  namespace Camera {
    Camera::Camera(int width, int height) {
      _width = width;
      _height = height;
    }

    void Camera::fromCamera(Camera* cam) {
      _fov      = cam->_fov     ;
      _position = cam->_position;
      _up       = cam->_up      ;
      _target   = cam->_target  ;
      _width    = cam->_width   ;
      _height   = cam->_height  ;
    }
  }
}