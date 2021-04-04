#include "Box.h"

#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>
#include "IyathuumCoreLib/lib/glm/gtc/type_ptr.hpp"

namespace Ahwassa {
  Box::Box(const glm::mat4& mat, const Iyathuum::Color& clr) {
    _matrix = mat;
    _color = clr;
  }

  void Box::setMatrix(const glm::mat4& mat) {
    _matrix = mat;
  }
  
  glm::mat4 Box::getMatrix() const {
    return _matrix;
  }

  void Box::setColor(const Iyathuum::Color& clr) {
    _color = clr;
  }

  Iyathuum::Color Box::getColor() const {
    return _color;
  }

  glm::mat4 Box::matrix() const {
    return _matrix;
  }
}