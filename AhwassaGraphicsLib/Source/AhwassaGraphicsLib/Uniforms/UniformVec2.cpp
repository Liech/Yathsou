#include "UniformVec2.h"

#include <glm/gtc/type_ptr.hpp>
#include "glad/glad.h"

namespace Ahwassa {
  glm::vec2 UniformVec2::getValue() const {
    return _value;
  }

  void UniformVec2::setValue(glm::vec2 val) {
    _value = val;
  }

  void UniformVec2::bind() {
    glUniform2fv(getLocation(), 1, glm::value_ptr(_value));
  }
}