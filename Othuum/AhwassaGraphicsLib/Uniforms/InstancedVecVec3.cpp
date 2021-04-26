#include "InstancedVecVec3.h"

#include "IyathuumCoreLib/lib/glm/gtc/type_ptr.hpp"
#include "glad/glad.h"

namespace Ahwassa {

  InstancedVecVec3::InstancedVecVec3(const std::string& name, int size) : Uniform(name) {
    _value.resize(size);
    _size = size;
    glGenBuffers(1, &instanceVBO);
  };

  InstancedVecVec3::~InstancedVecVec3() {
    glDeleteBuffers(1, &instanceVBO);
  }

  const std::vector<glm::vec3>& InstancedVecVec3::getValue() {
    return _value;
  }

  void InstancedVecVec3::setValue(const std::vector<glm::vec3>& val) {
    assert(val.size() == _size);
    _value = val;
  }

  void InstancedVecVec3::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * _value.size(), _value.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glVertexAttribPointer(getLocation(), 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribDivisor(getLocation(), 1);
  }
}