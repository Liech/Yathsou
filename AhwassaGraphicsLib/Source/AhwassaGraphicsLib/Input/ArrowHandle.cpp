#include "ArrowHandle.h"

#include "AhwassaGraphicsLib/Renderer/BasicBoxRenderer.h"

namespace Ahwassa {
  ArrowHandle::ArrowHandle(BasicBoxRenderer& renderer, const Iyathuum::Color& color) : _renderer(renderer) {
    _color = color;
  }

  void ArrowHandle::update() {

  }

  void ArrowHandle::draw() {
    _renderer.drawDot(_position, 0.2f, _color);
    _renderer.drawLine(_position, _direction + _position, 0.1f, _color);
  }

  void ArrowHandle::setPosition(const glm::vec3& position) {
    _position = position;
  }

  void ArrowHandle::setDirection(const glm::vec3& direction) {
    _direction = glm::normalize(direction);
  }

  glm::vec3 ArrowHandle::direction() const {
    return _direction;
  }

  glm::vec3 ArrowHandle::position() const {
    return _position;
  }

  void ArrowHandle::setOnMovedCallback(std::function<void()> onMoved) {
    _onMoved = onMoved;
  }
}