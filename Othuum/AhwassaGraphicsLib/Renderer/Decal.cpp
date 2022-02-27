#include "Decal.h"

#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>
#include "IyathuumCoreLib/lib/glm/gtc/type_ptr.hpp"

namespace Ahwassa {
  Decal::Decal(const glm::mat4& mat, const Iyathuum::Color& clr) {
    _matrix = mat;
    _color = clr;
  }

  void Decal::setMatrix(const glm::mat4& mat) {
    _matrix = mat;
  }
  
  glm::mat4 Decal::getMatrix() const {
    return _matrix;
  }

  void Decal::setColor(const Iyathuum::Color& clr) {
    _color = clr;
  }

  Iyathuum::Color Decal::getColor() const {
    return _color;
  }

  glm::mat4 Decal::matrix() const {
    return _matrix;
  }
}