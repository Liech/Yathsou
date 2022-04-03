#include "Dot.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Ahwassa {
  Dot::Dot(const glm::vec3& pos, const float& size, const Iyathuum::Color& clr) {
    _position = pos ;
    _size     = size;
    _color    = clr ;
    recalculate();
  }

  void Dot::setPosition(const glm::vec3& pos) {
    _position = pos;
    recalculate();
  }

  glm::vec3 Dot::getPosition() const {
    return _position;
  }

  void Dot::setSize(const float& size) {
    _size = size;
    recalculate();
  }

  float Dot::getSize() const {
    return _size;
  }

  void Dot::setColor(const Iyathuum::Color& clr) {
    _color = clr;
  }

  Iyathuum::Color Dot::getColor() const {
    return _color;
  }

  glm::mat4 Dot::matrix() const {
    return _matrix;
  }

  void Dot::recalculate() {
    const float x  = _position[0] - _size/2.0f;
    const float y  = _position[1] - _size/2.0f;
    const float z  = _position[2] - _size/2.0f;
    const float s  = _size;
    float transAndScale[16] = {
      s , 0 , 0, 0,
      0 , s , 0, 0,
      0 , 0 , s, 0,
      x , y , z, 1
    };

    _matrix = glm::make_mat4(transAndScale);
  }
}