#include "UniformVec4.h"

#include "IyathuumCoreLib/lib/glm/gtc/type_ptr.hpp"
#include "glad/glad.h"

namespace Ahwassa {
  glm::vec4 UniformVec4::getValue() {
    return _value;
  }

  void UniformVec4::setValue(glm::vec4 val) {
    _value = val;
  }

  void UniformVec4::bind() {
    glUniform4fv(getLocation(), 1, glm::value_ptr(_value));
  }
}