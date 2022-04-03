#include "UniformVecVec3.h"

#include <glm/gtc/type_ptr.hpp>
#include "glad/glad.h"

namespace Ahwassa {
  const std::vector<glm::vec3>& UniformVecVec3::getValue() {
    return _value;
  }

  void UniformVecVec3::setValue(const std::vector<glm::vec3>& val) {
    assert(val.size() == _size);
    _value = val;
  }

  void UniformVecVec3::bind() {
    glUniform3fv(getLocation(), _size, (const GLfloat*)_value.data());
  }
}