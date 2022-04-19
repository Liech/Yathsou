#include "UniformMat4.h"

#include <glm/gtc/type_ptr.hpp>
#include "glad/glad.h"

namespace Ahwassa {
  glm::mat4 UniformMat4::getValue() const {
    return _value;
  }

  void UniformMat4::setValue(const glm::mat4& val) {
    _value = val;
  }

  void UniformMat4::bind() {
    glUniformMatrix4fv(getLocation(), 1, GL_FALSE, glm::value_ptr(_value));
  }
}