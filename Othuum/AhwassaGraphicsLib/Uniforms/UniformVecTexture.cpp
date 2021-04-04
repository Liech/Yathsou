#include "UniformVecTexture.h"

#include "IyathuumCoreLib/lib/glm/gtc/type_ptr.hpp"
#include "glad/glad.h"

namespace Ahwassa {
  const std::vector<int>& UniformVecTexture::getValue() {
    return _value;
  }

  void UniformVecTexture::setValue(const std::vector<int>& val) {
    assert(val.size() == _size);
    _value = val;
  }

  void UniformVecTexture::bind() {
    //glUniform2fv(getLocation(), _size, (const GLfloat*)_value.data());
    ////glBindTextures(GL_TEXTURE0 + getLocation(), _size, (const GLuint*)_value.data());
    //int loc = getTextureLocation();
    //glActiveTexture(GL_TEXTURE0 + loc);
    //glBindTexture(GL_TEXTURE_2D, _texture);
    glUniform1iv(getLocation(), _size, (const GLint*)_value.data());
  }
}