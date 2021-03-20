#include "Camera2D.h"

#include "../OpenGL/Window.h"
#include "../OpenGL/Camera.h"
#include "IyathuumCoreLib/lib/glm/ext/matrix_transform.hpp"
#include "IyathuumCoreLib/lib/glm/vec2.hpp"
#include "IyathuumCoreLib/View2D.h"
#include "IyathuumCoreLib/BaseTypes/glmAABB.h"

#include <iostream>

namespace YolonaOss {
  namespace Camera {
    void Camera2D::load(std::shared_ptr<YolonaOss::Camera::Camera> camera, GL::Window* window) {
      _camera = camera;
      _window = window;
      //_window->setCursorStatus(GL::CursorStatus::HIDDEN);
      _lastCursorPos = glm::vec2((float)_window->getCursorPos().x, (float)_window->getCursorPos().y);
      _lastTime = _window->getTime();
      _view = std::make_shared<Iyathuum::View2D>(Iyathuum::glmAABB<2>(glm::vec2(0,0),glm::vec2(window->getWidth(),window->getHeight())));
    }

    Iyathuum::View2D& Camera2D::view() {
      return *_view;
    }

    void Camera2D::update() {
      _camera->set2D(true);
      _camera->set2DView(_view->getView());
      double time = _window->getTime();
      bool w = _window->getKeyStatus(GL::Key::KEY_W) == GL::KeyStatus::PRESS;
      bool a = _window->getKeyStatus(GL::Key::KEY_A) == GL::KeyStatus::PRESS;
      bool s = _window->getKeyStatus(GL::Key::KEY_S) == GL::KeyStatus::PRESS;
      bool d = _window->getKeyStatus(GL::Key::KEY_D) == GL::KeyStatus::PRESS;
      bool q = _window->getKeyStatus(GL::Key::KEY_Q) == GL::KeyStatus::PRESS;
      bool e = _window->getKeyStatus(GL::Key::KEY_E) == GL::KeyStatus::PRESS;
      bool speedup = _window->getKeyStatus(GL::Key::KEY_LEFT_SHIFT) == GL::KeyStatus::PRESS;

      float delta = (float)(time - _lastTime) * speedup ? 10 : 1;
      glm::vec3 toTarget = glm::normalize(_camera->getTarget() - _camera->getPosition());
      ////toTarget /= toTarget.length();
      glm::vec3 toSide = glm::cross(toTarget, _camera->getUp());
      if (w)
        _ortho += 0.01f;
      if (s)
        _ortho -= 0.01f;

      if (_ortho < 0)_ortho = 0;
      if (_ortho > 1) _ortho = 1;
      if (w || a || s || d || q || e) {
        if (w)
          _view->move(glm::vec2(0, 1));
        if (a)
          _view->move(glm::vec2(-1, 0));
        if (d)
          _view->move(glm::vec2(+1, 0));
        if (s)
          _view->move(glm::vec2(0,-1));

      }
      //  glm::vec3 offset(0, 0, 0);
      //  if (w) offset += toTarget * delta;
      //  if (s) offset += toTarget * -delta;
      //  if (a) offset += toSide * -delta;
      //  if (d) offset += toSide * delta;
      //  if (q) offset += _camera->getUp() * delta;
      //  if (e) offset += _camera->getUp() * -delta;
      //
      //  _camera->setPosition(_camera->getPosition() + offset);
      //  _camera->setTarget(_camera->getTarget() + offset);
      //}
      //int cx = (int)_window->getCursorPos().x;
      //int cy = (int)_window->getCursorPos().y;
      //glm::vec2 cursorMovement = glm::vec2(cx, cy) - glm::vec2(_lastCursorPos);
      //_window->setCursorPos(glm::vec2(_window->getWidth() / 2, _window->getHeight() / 2));
      //_lastCursorPos = glm::vec2((float)_window->getCursorPos().x, (float)_window->getCursorPos().y);

      //glm::vec4 lookDir = glm::vec4(glm::normalize(_camera->getTarget() - _camera->getPosition()), 1);
      //glm::mat4 rotationMat(1);
      //rotationMat = glm::rotate(rotationMat, 0.001f * -cursorMovement.x, glm::vec3(0.0, 1.0, 0.0));
      //glm::mat4 rotationMat2(1);
      //rotationMat2 = glm::rotate(rotationMat2, 0.001f * -cursorMovement.y, toSide);
      //glm::vec3 rotationResult = glm::vec3(rotationMat * rotationMat2 * lookDir);
      //glm::vec3 newTarget = rotationResult + _camera->getPosition();
      //_camera->setTarget(newTarget);

      _lastTime = time;
    }
  }
}