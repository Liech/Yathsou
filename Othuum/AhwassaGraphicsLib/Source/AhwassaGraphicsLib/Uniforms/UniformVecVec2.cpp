#include "UniformVecVec2.h"

#include <glm/gtc/type_ptr.hpp>
#include "glad/glad.h"

namespace Ahwassa {
  const std::vector<glm::vec2>& UniformVecVec2::getValue() {
    return _value;
  }

  void UniformVecVec2::setValue(const std::vector<glm::vec2>& val) {
    assert(val.size() == _size);
    _value = val;
  }

  void UniformVecVec2::bind() {
    glUniform2fv(getLocation(), _size, (const GLfloat*)_value.data());
  }
}