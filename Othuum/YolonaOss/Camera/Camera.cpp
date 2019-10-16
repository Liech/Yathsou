#include "Camera.h"
#include "../OpenGL/Window.h"
#include <glm/gtc/matrix_transform.hpp>

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

    glm::vec3 Camera::getPickRay(GL::Window* window) {
      //https://stackoverflow.com/questions/29997209/opengl-c-mouse-ray-picking-glmunproject
      // these positions must be in range [-1, 1] (!!!), not [0, width] and [0, height]
      auto mouse = window->getCursorPos();
      float mouseX = mouse.first  / ((float)window->getWidth()  * 0.5f) - 1.0f;
      float mouseY = mouse.second / ((float)window->getHeight() * 0.5f) - 1.0f;

      glm::mat4 proj = glm::perspective(glm::radians(getFOV()), getResolution()[0] / getResolution()[1], 0.1f, 100.0f);
      glm::mat4 view = glm::lookAt(getPosition(), getTarget(), getUp())* glm::mat4(1.0f);

      glm::mat4 invVP = glm::inverse(proj * view);
      glm::vec4 screenPos = glm::vec4(mouseX, -mouseY, 1.0f, 1.0f);
      glm::vec4 worldPos = invVP * screenPos;

      glm::vec3 dir = glm::normalize(glm::vec3(worldPos));

      return dir;
    }
  }
}