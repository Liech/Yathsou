#include "Sphere.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Ahwassa {
  Sphere::Sphere(const glm::vec3& pos, const float& size, const Iyathuum::Color& clr) {
    _position = pos ;
    _size     = size;
    _color    = clr ;
    recalculate();
  }

  void Sphere::setPosition(const glm::vec3& pos) {
    _position = pos;
    recalculate();
  }

  glm::vec3 Sphere::getPosition() const {
    return _position;
  }

  void Sphere::setSize(const float& size) {
    _size = size;
    recalculate();
  }

  float Sphere::getSize() const {
    return _size;
  }

  void Sphere::setColor(const Iyathuum::Color& clr) {
    _color = clr;
  }

  Iyathuum::Color Sphere::getColor() const {
    return _color;
  }

  glm::mat4 Sphere::matrix() const {
    return _matrix;
  }

  void Sphere::recalculate() {
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