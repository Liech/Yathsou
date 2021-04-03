#include "UniformVecMat4.h"

#include "IyathuumCoreLib/lib/glm/gtc/type_ptr.hpp"
#include "glad/glad.h"

namespace Ahwassa {
  const std::vector<glm::mat4>& UniformVecMat4::getValue() {
    return _value;
  }

  void UniformVecMat4::setValue(const std::vector<glm::mat4>& val) {
    assert(val.size() == _size);
    _value = val;
  }

  void UniformVecMat4::bind() {
    //for (int i = 0; i < _size; i++)
      glUniformMatrix4fv(getLocation(), _size, GL_FALSE, (const GLfloat*) _value.data());
  }
}