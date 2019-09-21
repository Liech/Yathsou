#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "glm/gtc/type_ptr.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "OpenGL/Window.h"
namespace YolonaOss {
  namespace GL {
    Camera::Camera(std::string name, int width, int height) : _view(name + "View"), _projection(name + "Projection"), _cameraPos(name + "Position"), _invViewProj(name + "inv") {
      _width = width;
      _height = height;
      _lastFrame = glfwGetTime();
    }

    void Camera::bind()
    {
      //http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/
      glm::mat4 Projection = glm::perspective(glm::radians(_fov), (float)_width / (float)_height, 0.1f, 100.0f);

      glm::mat4 View = glm::lookAt(
        getPosition(),
        getTarget(),
        getUp()
      );

      glm::mat4 Model = glm::mat4(1.0f);
      glm::mat4 mvp = Projection * View;

      _view.setValue(View);
      _projection.setValue(Projection);
      _invViewProj.setValue(glm::inverse(mvp));
      _cameraPos.setValue(getPosition());
    }

    glm::vec3 Camera::getPosition() {
      return _position;
    }
    void Camera::setPosition(glm::vec3 v) {
      _position = v;
    }

    std::vector<Uniform*> Camera::getUniforms() {
      return std::vector<Uniform*> {&_view, & _projection, & _cameraPos, & _invViewProj};
    }
  }
}