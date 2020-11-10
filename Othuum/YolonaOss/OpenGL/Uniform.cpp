#include "Uniform.h"

#include "IyathuumCoreLib/lib/glm/gtc/type_ptr.hpp"
#include "glad/glad.h"
namespace YolonaOss {
  namespace GL {
    std::string Uniform::toGLSL() {
      return "layout(location = " + std::to_string(getLocation()) + ") uniform " + getType() + " " + getName() + getArrayPostfix() + ";\n";
    }

    float UniformFloat::getValue() {
      return _value;
    }

    void UniformFloat::setValue(float val) {
      _value = val;
    }

    void UniformFloat::bind() {
      glUniform1f(getLocation(), _value);
    }

    glm::vec2 UniformVec2::getValue() {
      return _value;
    }

    void UniformVec2::setValue(glm::vec2 val) {
      _value = val;
    }

    void UniformVec2::bind() {
      glUniform2fv(getLocation(), 1, glm::value_ptr(_value));
    }


    glm::vec3 UniformVec3::getValue() {
      return _value;
    }

    void UniformVec3::setValue(glm::vec3 val) {
      _value = val;
    }

    void UniformVec3::bind() {
      glUniform3fv(getLocation(), 1, glm::value_ptr(_value));
    }

    glm::vec4 UniformVec4::getValue() {
      return _value;
    }

    void UniformVec4::setValue(glm::vec4 val) {
      _value = val;
    }

    void UniformVec4::bind() {
      glUniform4fv(getLocation(), 1, glm::value_ptr(_value));
    }

    glm::mat4 UniformMat4::getValue() {
      return _value;
    }

    void UniformMat4::setValue(glm::mat4 val) {
      _value = val;
    }

    void UniformMat4::bind() {
      glUniformMatrix4fv(getLocation(), 1, GL_FALSE, glm::value_ptr(_value));
    }

    const std::vector<glm::mat4>& UniformVecMat4::getValue() {
      return _value;
    }

    void UniformVecMat4::setValue(const std::vector<glm::mat4> val) {
      assert(val.size() == _size);
      _value = val;
    }

    void UniformVecMat4::bind() {
      for(int i = 0; i <_size;i++)
        glUniformMatrix4fv(getLocation()+i, 1, GL_FALSE, glm::value_ptr(_value[i]));
      
    }
  }
}