#include "Camera.h"
#include <IyathuumCoreLib/lib/glm/glm.hpp>
#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>
#include "IyathuumCoreLib/lib/glm/gtc/type_ptr.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "OpenGL/Window.h"
namespace YolonaOss {
  namespace GL {
    Camera::Camera(std::string name, int width, int height) : YolonaOss::Camera::Camera(width,height), _view(name + "View"), _projection(name + "Projection"), _cameraPos(name + "Position"), _invViewProj(name + "inv") {
      _lastFrame = glfwGetTime();
    }
    Camera::Camera(std::string name, YolonaOss::Camera::Camera* cam) : YolonaOss::Camera::Camera((int)cam->getResolution()[0], (int)cam->getResolution()[1]), _view(name + "View"), _projection(name + "Projection"), _cameraPos(name + "Position"), _invViewProj(name + "inv") {
      _lastFrame = glfwGetTime();
      fromCamera(cam);
    }

    void Camera::bind()
    {
      //http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/
      glm::mat4 Projection = getProjectionMatrix();

      glm::mat4 View = getViewMatrix();

      glm::mat4 Model = glm::mat4(1.0f);
      glm::mat4 mvp = Projection * View;

      _view.setValue(View);
      _projection.setValue(Projection);
      _invViewProj.setValue(glm::inverse(mvp));
      _cameraPos.setValue(getPosition());
    }

    std::vector<Uniform*> Camera::getUniforms() {
      return std::vector<Uniform*> {&_view, & _projection, & _cameraPos, & _invViewProj};
    }
  }
}