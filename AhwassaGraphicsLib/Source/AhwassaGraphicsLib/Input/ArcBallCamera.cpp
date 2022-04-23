#include "ArcBallCamera.h"

#include "AhwassaGraphicsLib/Core/Camera.h"
#include "AhwassaGraphicsLib/Input/Input.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "AhwassaGraphicsLib/Util.h"
#include <imgui.h>

namespace Ahwassa {
  ArcBallCamera::ArcBallCamera(std::shared_ptr<Camera> cam, Input& inp) : _input(inp) {
    _camera = cam;
    setLocalPosition(Iyathuum::glmAABB<2>(glm::vec2(0, 0), cam->getResolution()));
  }

  bool ArcBallCamera::mouseClickEvent(const glm::vec2& localPosition, const Iyathuum::Key& button) {
    return true;
  }

  bool ArcBallCamera::mouseMoveEvent(const glm::vec2& current, const  glm::vec2& movement) {
    if (_arcAround)
      move(movement, glm::vec2(0, 0), true);
    if (_panAround) {
      float distance = glm::distance(_camera->getTarget(), _camera->getPosition());
      _camera->moveTo(_camera->getTarget() - distance * 0.001f * _camera->getRight() * movement[0] - distance * 0.001f * _camera->getCamUp() * movement[1]);
    }
    return true;
  }

  void ArcBallCamera::move(const glm::vec2& mouse, const glm::vec2& wheel, bool setCursor) {
    glm::vec3 toSide = _camera->getRight();
    glm::vec4 lookDir = glm::vec4(_camera->getDir(), 1);
    glm::mat4 rotationMat(1);
    rotationMat = glm::rotate(rotationMat, 0.001f * -mouse.x, _camera->getUp());
    glm::mat4 rotationMat2(1);
    rotationMat2 = glm::rotate(rotationMat2, 0.001f * mouse.y, toSide);
    glm::vec3 rotationResult = glm::vec3(rotationMat * rotationMat2 * lookDir);
    rotationResult = glm::normalize(rotationResult);
    float distance = glm::distance(_camera->getPosition(), _camera->getTarget()) - wheel[1];
    if (distance < 1) 
      distance = 1;

    glm::vec3 plane = glm::cross(_camera->getRight(), _camera->getUp());
    float before = glm::orientedAngle(plane, _camera->getDir(), _camera->getRight()) / (glm::pi<float>() / 2);
    float after = glm::orientedAngle(plane, rotationResult, _camera->getRight()) / (glm::pi<float>() / 2);

    if (std::floor(std::abs(before)) != std::floor(std::abs(after))) {
      rotationResult = glm::vec3(rotationMat * lookDir);
      rotationResult = glm::normalize(rotationResult);
    }

    _camera->setPosition(_camera->getTarget() - rotationResult * distance);
    _camera->setRight(rotationMat * glm::vec4(_camera->getRight(), 1));
  }

  bool ArcBallCamera::mouseWheelEvent(const glm::vec2& movement) {
    if (ImGui::GetIO().WantCaptureMouse) {
      return true;
    }
    move(glm::vec2(0, 0), movement, false);
    return true;
  }

  bool ArcBallCamera::mouseEvent(const glm::vec2& localPosition, const Iyathuum::Key& button, const Iyathuum::KeyStatus& status) {
    if (ImGui::GetIO().WantCaptureMouse) {
      _arcAround = false;
      return true;
    }
    bool returnValue = false;

    if (button == Iyathuum::Key::MOUSE_BUTTON_1 && status == Iyathuum::KeyStatus::PRESS) {
      _arcAround = true;
      returnValue = true;
    }
    else if (button == Iyathuum::Key::MOUSE_BUTTON_1 && status == Iyathuum::KeyStatus::RELEASE) {
      _arcAround = false;
      returnValue = true;
    }

    bool pan = button == Iyathuum::Key::MOUSE_BUTTON_3 || button == Iyathuum::Key::MOUSE_BUTTON_2;
    if (pan && status == Iyathuum::KeyStatus::PRESS) {
      _panAround = true;
      returnValue = true;
    }
    if (pan && status == Iyathuum::KeyStatus::RELEASE) {
      _panAround = false;
      returnValue = true;
    }
    return returnValue;
  }

  void ArcBallCamera::update() {
    glm::vec3 toSide = glm::cross(_camera->getDir(), _camera->getUp());
    glm::vec3 toUp = glm::cross(_camera->getDir(), toSide);
    _camera->setPosition(_camera->getPosition());
  }

  bool ArcBallCamera::keyEvent(const Iyathuum::Key& button, const Iyathuum::KeyStatus& status) {
    if (ImGui::GetIO().WantCaptureMouse) {
      _arcAround = false;
      return true;
    }
    if (button == Iyathuum::Key::MOUSE_BUTTON_1 && status == Iyathuum::KeyStatus::PRESS) {
      _arcAround = !_arcAround;
      return true;
    }
    return false;
  }
}