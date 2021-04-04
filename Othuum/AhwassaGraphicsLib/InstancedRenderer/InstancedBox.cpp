#include "InstancedBox.h"

#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>
#include "IyathuumCoreLib/lib/glm/gtc/type_ptr.hpp"

namespace Ahwassa {
  InstancedBox::InstancedBox(const glm::mat4& mat, const Iyathuum::Color& clr) {
    _matrix = mat;
    _color = clr;
  }

  void InstancedBox::setMatrix(const glm::mat4& mat) {
    _matrix = mat;
  }
  
  glm::mat4 InstancedBox::getMatrix() const {
    return _matrix;
  }

  void InstancedBox::setColor(const Iyathuum::Color& clr) {
    _color = clr;
  }

  Iyathuum::Color InstancedBox::getColor() const {
    return _color;
  }

  glm::mat4 InstancedBox::matrix() const {
    return _matrix;
  }
}