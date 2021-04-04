#include "FreeCamera.h"

#include "Core/Camera.h"
#include "Input/Input.h"
#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>

namespace Ahwassa {
  FreeCamera::FreeCamera(std::shared_ptr<Camera> cam, Input& inp) : _input(inp) {
    _camera = cam;
    setLocalPosition(Iyathuum::glmAABB<2>(glm::vec2(0, 0), cam->getResolution()));
  }

  bool FreeCamera::mouseClickEvent(glm::vec2 localPosition, Iyathuum::Key button) {
    if (button != Iyathuum::Key::MOUSE_BUTTON_1)
      return false;
    _focus = !_focus;
    _input.setCursorStatus(_focus?Iyathuum::CursorStatus::HIDDEN:Iyathuum::CursorStatus::NORMAL);
    return true;
  }

  bool FreeCamera::mouseMoveEvent(glm::vec2 movement) {
    if (!_focus)
      return false;
    _input.setCursorPos(_camera->getResolution() / 2.0f);


    glm::vec3 toSide = glm::cross(_camera->getDir(), _camera->getUp());
    glm::vec4 lookDir = glm::vec4(_camera->getDir(),1);
    glm::mat4 rotationMat(1);
    rotationMat = glm::rotate(rotationMat, 0.00001f * -movement.x, glm::vec3(0.0, 1.0, 0.0));
    glm::mat4 rotationMat2(1);
    rotationMat2 = glm::rotate(rotationMat2, 0.00001f * -movement.y, toSide);
    glm::vec3 rotationResult = glm::vec3(rotationMat * rotationMat2 * lookDir);
    glm::vec3 newTarget = rotationResult + _camera->getPosition();
    _camera->setTarget(newTarget);

    return true;
  }

  bool FreeCamera::mouseWheelEvent(glm::vec2 movement) {
    auto dir = _camera->getDir();
    _camera->setPosition(_camera->getPosition() + _camera->getDir() * movement[1]);
    _camera->setDir(dir);
    return true;
  }

  bool FreeCamera::keyEvent(Iyathuum::Key button, Iyathuum::KeyStatus status) {
    if (!_focus)
      return false;

    return true;
  }
}