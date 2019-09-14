#include "FreeCamera.h"

#include "YolonaOss/OpenGL/Window.h"
#include "YolonaOss/OpenGL/Camera.h"
#include "YolonaOss/glm/ext/matrix_transform.hpp"

#include <iostream>

FreeCamera::FreeCamera(Window* window) {
  _window = window;
  _lastTime = _window->getTime();
}

void FreeCamera::load(std::shared_ptr<Camera> camera) {
  _camera = camera;
  _window->setCursorStatus(CursorStatus::HIDDEN);
  _window->setCatchCursor(true);
}

void FreeCamera::update() {
  double time = _window->getTime();
  bool w = _window->getKeyStatus(KeyboardKey::KEY_W)== KeyStatus::PRESS;
  bool a = _window->getKeyStatus(KeyboardKey::KEY_A)== KeyStatus::PRESS;
  bool s = _window->getKeyStatus(KeyboardKey::KEY_S)== KeyStatus::PRESS;
  bool d = _window->getKeyStatus(KeyboardKey::KEY_D) == KeyStatus::PRESS;
  bool q = _window->getKeyStatus(KeyboardKey::KEY_Q) == KeyStatus::PRESS;
  bool e = _window->getKeyStatus(KeyboardKey::KEY_E) == KeyStatus::PRESS;

  float delta = (time - _lastTime);
  glm::vec3 toTarget = glm::normalize(_camera->getTarget() - _camera->getPosition());
  ////toTarget /= toTarget.length();
  glm::vec3 toSide = glm::cross(toTarget, _camera->getUp());

  if (w || a || s || d || q || e) {
    glm::vec3 offset(0,0,0);
    if (w) offset += toTarget * delta;
    if (s) offset += toTarget * -delta;
    if (a) offset += toSide * -delta;
    if (d) offset += toSide * delta;
    if (q) offset += _camera->getUp() * delta;
    if (e) offset += _camera->getUp() * -delta;

    _camera->setPosition(_camera->getPosition() + offset);
    _camera->setTarget(_camera->getTarget() + offset);
  }

  glm::vec2 cursorMovement(_window->getCursorMovement().first, _window->getCursorMovement().second);
  
  glm::vec4 lookDir = glm::vec4(glm::normalize(_camera->getTarget() - _camera->getPosition()),1);
  glm::mat4 rotationMat(1);
  rotationMat = glm::rotate(rotationMat, 0.001f * -cursorMovement.x, glm::vec3(0.0, 1.0, 0.0));
  glm::mat4 rotationMat2(1);
  rotationMat2 = glm::rotate(rotationMat2, 0.001f * -cursorMovement.y, toSide);
  glm::vec3 rotationResult = glm::vec3(rotationMat * rotationMat2 * lookDir);
  glm::vec3 newTarget = rotationResult + _camera->getPosition();
  _camera->setTarget(newTarget);

  _lastTime = time;
}