#include "RTSCamera.h"

#include "../OpenGL/Window.h"
#include "../OpenGL/Camera.h"
#include "IyathuumCoreLib/lib/glm/ext/matrix_transform.hpp"
#include "IyathuumCoreLib/lib/glm/vec2.hpp"

#include <iostream>

namespace YolonaOss {
  namespace Camera {
    void RTSCamera::load(std::shared_ptr<YolonaOss::Camera::Camera> camera, GL::Window* window) {
      _camera = camera;
      _lastTime = _window->getTime();
      _window = window;
    }

    void RTSCamera::update() {
      double time = _window->getTime();
      float delta = (float)(time - _lastTime);
      bool w = _window->getKeyStatus(GL::Key::KEY_W) == GL::KeyStatus::PRESS;
      bool a = _window->getKeyStatus(GL::Key::KEY_A) == GL::KeyStatus::PRESS;
      bool s = _window->getKeyStatus(GL::Key::KEY_S) == GL::KeyStatus::PRESS;
      bool d = _window->getKeyStatus(GL::Key::KEY_D) == GL::KeyStatus::PRESS;

      glm::vec3 toTarget = glm::normalize(_camera->getTarget() - _camera->getPosition());
      glm::vec3 toSide = glm::cross(toTarget, _camera->getUp());
      glm::vec2 mouse = glm::vec2(_window->getCursorPos().x, _window->getCursorPos().y);
      glm::vec2 newMouse = mouse;
      glm::vec3 offset(0, 0, 0);
      if (mouse.x < 0) { newMouse.x = 0.0f;                        offset += toSide * 0.001f * mouse.x; }
      if (mouse.x > _window->getWidth()) { newMouse.x = (float)_window->getWidth();  offset += toSide * 0.001f * (mouse.x - _window->getWidth()); }
      if (mouse.y < 0) { newMouse.y = 0.0f;                        offset += _camera->getUp() * 0.001f * -mouse.y; }
      if (mouse.y > _window->getHeight()) { newMouse.y = (float)_window->getHeight(); offset += _camera->getUp() * 0.001f * -(mouse.y - _window->getHeight()); }

      if (w) offset += _camera->getUp() * delta;
      if (s) offset += _camera->getUp() * -delta;
      if (a) offset += toSide * -delta;
      if (d) offset += toSide * delta;

      offset += toTarget * _window->getMouseWheelMovement();

      _camera->setPosition(_camera->getPosition() + offset);
      _camera->setTarget(_camera->getTarget() + offset);
      _window->setCursorPos(glm::vec2(newMouse.x, newMouse.y));
      _lastTime = _window->getTime();

    }
  }
}