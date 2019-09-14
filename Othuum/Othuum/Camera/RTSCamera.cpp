#include "RTSCamera.h"

#include "YolonaOss/OpenGL/Window.h"
#include "YolonaOss/OpenGL/Camera.h"
#include "YolonaOss/glm/ext/matrix_transform.hpp"
#include "YolonaOss/glm/vec2.hpp"

#include <iostream>

RTSCamera::RTSCamera(Window* window) {
  _window = window;
  _lastTime = _window->getTime();
}

void RTSCamera::load(std::shared_ptr<Camera> camera) {
  _camera = camera;
}

void RTSCamera::update() {
  double time = _window->getTime();
  float delta = (time - _lastTime);
  bool w = _window->getKeyStatus(KeyboardKey::KEY_W) == KeyStatus::PRESS;
  bool a = _window->getKeyStatus(KeyboardKey::KEY_A) == KeyStatus::PRESS;
  bool s = _window->getKeyStatus(KeyboardKey::KEY_S) == KeyStatus::PRESS;
  bool d = _window->getKeyStatus(KeyboardKey::KEY_D) == KeyStatus::PRESS;
  
  glm::vec3 toTarget = glm::normalize(_camera->getTarget() - _camera->getPosition());
  glm::vec3 toSide = glm::cross(toTarget, _camera->getUp());
  glm::vec2 mouse = glm::vec2(_window->getCursorPos().first,_window->getCursorPos().second);  
  glm::vec2 newMouse = mouse;
  glm::vec3 offset(0,0,0);
  if (mouse.x < 0)                    { newMouse.x = 0;                    offset += toSide           * 0.001f *  mouse.x; }
  if (mouse.x > _window->getWidth())  { newMouse.x = _window->getWidth();  offset += toSide           * 0.001f *  (mouse.x- _window->getWidth()); }
  if (mouse.y < 0)                    { newMouse.y = 0;                    offset += _camera->getUp() * 0.001f * -mouse.y; }
  if (mouse.y > _window->getHeight()) { newMouse.y = _window->getHeight(); offset += _camera->getUp() * 0.001f *  -(mouse.y - _window->getHeight()); }

  if (w) offset += _camera->getUp() * delta;
  if (s) offset += _camera->getUp() * -delta;
  if (a) offset += toSide   * -delta;
  if (d) offset += toSide   * delta;



  _camera->setPosition(_camera->getPosition() + offset);
  _camera->setTarget(_camera->getTarget() + offset);
  _window->setCursorPos(std::make_pair(newMouse.x, newMouse.y));
  _lastTime = _window->getTime();

}