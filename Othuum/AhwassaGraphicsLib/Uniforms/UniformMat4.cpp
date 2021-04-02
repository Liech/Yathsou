#include "UniformMat4.h"

#include "IyathuumCoreLib/lib/glm/gtc/type_ptr.hpp"
#include "glad/glad.h"

namespace Ahwassa {
  glm::mat4 UniformMat4::getValue() {
    return _value;
  }

  void UniformMat4::setValue(glm::mat4 val) {
    _value = val;
  }

  void UniformMat4::bind() {
    glUniformMatrix4fv(getLocation(), 1, GL_FALSE, glm::value_ptr(_value));
  }
}