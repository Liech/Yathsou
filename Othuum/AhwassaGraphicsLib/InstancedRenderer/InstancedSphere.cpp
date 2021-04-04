#include "InstancedSphere.h"

#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>
#include "IyathuumCoreLib/lib/glm/gtc/type_ptr.hpp"

namespace Ahwassa {
  InstancedSphere::InstancedSphere(const glm::vec3& pos, const float& size, const Iyathuum::Color& clr) {
    _position = pos ;
    _size     = size;
    _color    = clr ;
    recalculate();
  }

  void InstancedSphere::setPosition(const glm::vec3& pos) {
    _position = pos;
    recalculate();
  }

  glm::vec3 InstancedSphere::getPosition() const {
    return _position;
  }

  void InstancedSphere::setSize(const float& size) {
    _size = size;
    recalculate();
  }

  float InstancedSphere::getSize() const {
    return _size;
  }

  void InstancedSphere::setColor(const Iyathuum::Color& clr) {
    _color = clr;
  }

  Iyathuum::Color InstancedSphere::getColor() const {
    return _color;
  }

  glm::mat4 InstancedSphere::matrix() const {
    return _matrix;
  }

  void InstancedSphere::recalculate() {
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