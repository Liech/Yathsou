#include "Camera.h"
#include "../OpenGL/Window.h"
#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>
#include <IyathuumCoreLib/lib/glm/ext/matrix_projection.hpp>
#include <IyathuumCoreLib/lib/glm/gtc/matrix_access.hpp>
#include <iostream>
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

    glm::mat4 Camera::getProjectionMatrix() {
      return glm::perspective(glm::radians(getFOV()), getResolution()[0] / getResolution()[1], getNearPlane(), getFarPlane());
    }

    glm::mat4 Camera::getViewMatrix() {
      return glm::lookAt(getPosition(),getTarget(),getUp());
    }

    glm::vec2 Camera::worldToViewCoordTransform(glm::vec3 worldPos)
    {
      //https://stackoverflow.com/questions/8491247/c-opengl-convert-world-coords-to-screen2d-coords
      glm::vec4 clipSpacePos = getProjectionMatrix() * (glm::lookAt(getPosition(), getTarget(), getUp()) * glm::vec4(worldPos, 1.0));
      glm::vec3 ndcSpacePos = clipSpacePos / clipSpacePos.w;
      float x = ((ndcSpacePos[0] + 1.0) / 2.0) * getResolution()[0];
      float y = ((ndcSpacePos[1] + 1.0) / 2.0) * getResolution()[1];
      return glm::vec2(x,y);
    }

    // SCREEN SPACE: mouse_x and mouse_y are screen space
    glm::vec3 Camera::viewToWorldCoordTransform(int mouse_x, int mouse_y) {
    // NORMALISED DEVICE SPACE
    double x = 2.0 * mouse_x / getResolution()[0] - 1;
    double y = 2.0 * mouse_y / getResolution()[1] - 1;

    // HOMOGENEOUS SPACE
    glm::vec4 screenPos = glm::vec4(x, -y, -1.0f, 1.0f);

    // Projection/Eye Space
    glm::mat4 ProjectView = getProjectionMatrix() * glm::lookAt(glm::vec3(0,0,0), glm::normalize(getTarget() - getPosition()), getUp());// getViewMatrix();
    glm::mat4 viewProjectionInverse = inverse(ProjectView);

    glm::vec4 worldPos = viewProjectionInverse * screenPos;
    return glm::vec3(worldPos);
  }

    glm::vec3 Camera::getPickRay(float X, float Y) {
      glm::vec3 worldMouse = viewToWorldCoordTransform(X, Y);
      return worldMouse; 
    }
  }
}