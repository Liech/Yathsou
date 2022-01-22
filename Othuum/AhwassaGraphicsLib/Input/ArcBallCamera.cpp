#include "ArcBallCamera.h"

#include "Core/Camera.h"
#include "Input/Input.h"
#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>
#include "Util.h"

namespace Ahwassa {
  ArcBallCamera::ArcBallCamera(std::shared_ptr<Camera> cam, Input& inp, Iyathuum::Key toggleKey) : _input(inp) {
    _camera = cam;
    _toggleKey = toggleKey;
    setLocalPosition(Iyathuum::glmAABB<2>(glm::vec2(0, 0), cam->getResolution()));
  }

  bool ArcBallCamera::isFocus() {
    return _focus;
  }

  void ArcBallCamera::setFocus(bool focus) {
    _focus = focus;
    _input.setCursorStatus(_focus ? Iyathuum::CursorStatus::HIDDEN : Iyathuum::CursorStatus::NORMAL);
    _input.setCursorPos(_camera->getResolution() / 2.0f);
    _input.resetCursorMovement(_camera->getResolution() / 2.0f);
  }

  bool ArcBallCamera::mouseClickEvent(const glm::vec2& localPosition, const Iyathuum::Key& button) {
    return true;
  }

  bool ArcBallCamera::mouseMoveEvent(const glm::vec2& current, const  glm::vec2& movement) {
    if (!isFocus())
      return false;
    move(movement, glm::vec2(0, 0), true);
    return true;
  }

  void ArcBallCamera::move(const glm::vec2& mouse, const glm::vec2& wheel, bool setCursor) {
    if (setCursor) {
      _input.setCursorPos(_camera->getResolution() / 2.0f);
      _input.resetCursorMovement(_camera->getResolution() / 2.0f);
    }

    glm::vec3 toSide = glm::cross(_camera->getDir(), _camera->getUp());
    glm::vec4 lookDir = glm::vec4(_camera->getDir(), 1);
    glm::mat4 rotationMat(1);
    rotationMat = glm::rotate(rotationMat, 0.001f * -mouse.x, glm::vec3(0.0, 1.0, 0.0));
    glm::mat4 rotationMat2(1);
    rotationMat2 = glm::rotate(rotationMat2, 0.001f * mouse.y, toSide);
    glm::vec3 rotationResult = glm::vec3(rotationMat * rotationMat2 * lookDir);
    rotationResult = glm::normalize(rotationResult);
    float distance = glm::distance(_camera->getPosition(), _camera->getTarget()) - wheel[1];
    if (distance < 1) distance = 1;
    _camera->setPosition(_camera->getTarget() - rotationResult * distance);
  }

  bool ArcBallCamera::mouseWheelEvent(const glm::vec2& movement) {
    move(glm::vec2(0, 0), movement, false);
    return true;
  }

  bool ArcBallCamera::mouseEvent(const glm::vec2& localPosition, const Iyathuum::Key& button, const Iyathuum::KeyStatus& status) {
    if (button == _toggleKey && status == Iyathuum::KeyStatus::PRESS) {
      setFocus(!isFocus());
      return true;
    }
    return false;
  }

  void ArcBallCamera::update() {
    glm::vec3 toSide = glm::cross(_camera->getDir(), _camera->getUp());
    glm::vec3 toUp = glm::cross(_camera->getDir(), toSide);
    _camera->setPosition(_camera->getPosition());
  }

  bool ArcBallCamera::keyEvent(const Iyathuum::Key& button, const Iyathuum::KeyStatus& status) {
    if (button == _toggleKey && status == Iyathuum::KeyStatus::PRESS) {
      setFocus(!isFocus());
      return true;
    }
    return false;
  }
}