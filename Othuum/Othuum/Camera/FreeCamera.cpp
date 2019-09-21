#include "FreeCamera.h"

#include "YolonaOss/OpenGL/Window.h"
#include "YolonaOss/OpenGL/Camera.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/vec2.hpp"

#include <iostream>

FreeCamera::FreeCamera(Window* window) : _lastCursorPos(0,0){
  _window = window;
  _lastTime = _window->getTime();
}

void FreeCamera::load(std::shared_ptr<Camera> camera) {
  _camera = camera;
  _window->setCursorStatus(CursorStatus::HIDDEN);
  _lastCursorPos = glm::vec2((float)_window->getCursorPos().first, (float)_window->getCursorPos().second);
}

void FreeCamera::update() {
  double time = _window->getTime();
  bool w = _window->getKeyStatus(Key::KEY_W)== KeyStatus::PRESS;
  bool a = _window->getKeyStatus(Key::KEY_A)== KeyStatus::PRESS;
  bool s = _window->getKeyStatus(Key::KEY_S)== KeyStatus::PRESS;
  bool d = _window->getKeyStatus(Key::KEY_D) == KeyStatus::PRESS;
  bool q = _window->getKeyStatus(Key::KEY_Q) == KeyStatus::PRESS;
  bool e = _window->getKeyStatus(Key::KEY_E) == KeyStatus::PRESS;

  float delta = (float)(time - _lastTime);
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
  int cx = (int)_window->getCursorPos().first;
  int cy = (int)_window->getCursorPos().second;
  glm::vec2 cursorMovement = glm::vec2(cx,cy) - glm::vec2(_lastCursorPos);
  _window->setCursorPos(std::make_pair(_window->getWidth() / 2, _window->getHeight() / 2));
  _lastCursorPos = glm::vec2((float)_window->getCursorPos().first, (float)_window->getCursorPos().second);

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