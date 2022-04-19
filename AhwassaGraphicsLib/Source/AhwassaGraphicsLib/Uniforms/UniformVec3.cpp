#include "UniformVec3.h"

#include <glm/gtc/type_ptr.hpp>
#include "glad/glad.h"

namespace Ahwassa {
  glm::vec3 UniformVec3::getValue() const {
    return _value;
  }

  void UniformVec3::setValue(const glm::vec3& val) {
    _value = val;
  }

  void UniformVec3::bind() {
    glUniform3fv(getLocation(), 1, glm::value_ptr(_value));
  }
}