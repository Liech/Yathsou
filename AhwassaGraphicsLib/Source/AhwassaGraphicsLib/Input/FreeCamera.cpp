#include "FreeCamera.h"

#include "AhwassaGraphicsLib/Core/Camera.h"
#include "AhwassaGraphicsLib/Input/Input.h"
#include "AhwassaGraphicsLib/Util.h"
#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>

namespace Ahwassa {
  FreeCamera::FreeCamera(std::shared_ptr<Camera> cam, Input& inp, Iyathuum::Key toggleKey) : _input(inp) {
    _camera = cam;
    _toggleKey = toggleKey;
    setLocalPosition(Iyathuum::glmAABB<2>(glm::vec2(0, 0), cam->getResolution()));
  }

  bool FreeCamera::isFocus() {
    return _focus;
  }

  void FreeCamera::setFocus(bool focus) {
    _focus = focus;
    _input.setCursorStatus(_focus ? Iyathuum::CursorStatus::HIDDEN : Iyathuum::CursorStatus::NORMAL);
    if (focus) {
      _input.setCursorPos((glm::vec2)_camera->getResolution() / 2.0f);
      _input.resetCursorMovement((glm::vec2)_camera->getResolution() / 2.0f);
    }
  }

  bool FreeCamera::mouseClickEvent(const glm::vec2& localPosition, const Iyathuum::Key& button) {
    return true;
  }

  bool FreeCamera::mouseMoveEvent(const glm::vec2& current, const glm::vec2& movement) {
    if (!isFocus())
      return false;
    _input.setCursorPos((glm::vec2)_camera->getResolution() / 2.0f);
    _input.resetCursorMovement((glm::vec2)_camera->getResolution() / 2.0f);

    glm::vec3 toSide = glm::cross(_camera->getDir(), _camera->getUp());
    glm::vec4 lookDir = glm::vec4(_camera->getDir(),1);
    glm::mat4 rotationMat(1);
    rotationMat = glm::rotate(rotationMat, 0.001f * -movement.x, glm::vec3(0.0, 1.0, 0.0));
    glm::mat4 rotationMat2(1);
    rotationMat2 = glm::rotate(rotationMat2, 0.001f * movement.y, toSide);
    glm::vec3 rotationResult = glm::vec3(rotationMat * rotationMat2 * lookDir);
    glm::vec3 newTarget = rotationResult + _camera->getPosition();
    _camera->setTarget(newTarget);
    return true;
  }

  bool FreeCamera::mouseWheelEvent(const glm::vec2& movement) {
    auto dir = _camera->getDir();
    _camera->setPosition(_camera->getPosition() + _camera->getDir() * movement[1]);
    _camera->setDir(dir);
    return true;
  }

  bool FreeCamera::mouseEvent(const glm::vec2& localPosition, const Iyathuum::Key& button, const Iyathuum::KeyStatus& status) {
    if (ImGui::GetIO().WantCaptureMouse) {
      setFocus(false);
      return true;
    }
    if (button == _toggleKey && status == Iyathuum::KeyStatus::PRESS) {
      setFocus(!isFocus());
      return true;
    }
    return false;
  }

  bool FreeCamera::keyEvent(const Iyathuum::Key& button, const  Iyathuum::KeyStatus& status) {
    if (button == _toggleKey && status == Iyathuum::KeyStatus::PRESS)
      setFocus(!isFocus());
    if (!isFocus())
      return false;
    if (button == Iyathuum::Key::KEY_A) {
      if (status == Iyathuum::KeyStatus::PRESS)
        _moveX = -1;
      if (status == Iyathuum::KeyStatus::RELEASE)
        _moveX = std::max(_moveX, 0.0f);
    }
    if (button == Iyathuum::Key::KEY_D) {
      if (status == Iyathuum::KeyStatus::PRESS)
        _moveX = 1;
      if (status == Iyathuum::KeyStatus::RELEASE)
        _moveX = std::min(_moveX, 0.0f);
    }
    if (button == Iyathuum::Key::KEY_W) {
      if (status == Iyathuum::KeyStatus::PRESS)
        _moveY = -1;
      if (status == Iyathuum::KeyStatus::RELEASE)
        _moveY = std::max(_moveY, 0.0f);
    }
    if (button == Iyathuum::Key::KEY_S) {
      if (status == Iyathuum::KeyStatus::PRESS)
        _moveY = 1;
      if (status == Iyathuum::KeyStatus::RELEASE)
        _moveY = std::min(_moveY, 0.0f);
    }
    if (button == Iyathuum::Key::KEY_F1) {
      if (status == Iyathuum::KeyStatus::RELEASE)
        _wireframe = !_wireframe;
      Util::setWireframe(_wireframe);
    }

    return true;
  }

  void FreeCamera::update() {
    glm::vec3 toSide = glm::cross(_camera->getDir(), _camera->getUp());
    glm::vec3 toUp = glm::cross(_camera->getDir(), toSide);
    auto dir = _camera->getDir();
    _camera->setPosition(_camera->getPosition() + _moveX * toSide + _moveY * toUp);
    _camera->setDir(dir);
  }   
  
  void FreeCamera::endFocusEvent() {
    setFocus(false);
  }

}