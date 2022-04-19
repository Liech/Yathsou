#include "InstancedVecMat4.h"

#include <glm/gtc/type_ptr.hpp>
#include "glad/glad.h"

namespace Ahwassa {
  InstancedVecMat4::InstancedVecMat4(const std::string& name, int size) : Uniform(name) { 
    _value.resize(size); 
    _size = size; 
    for (size_t i = 0; i < _value.size(); i++) {
      _value[i] = glm::mat4(1.0);
    }

    glGenBuffers(1, &instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * _value.size(), _value.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  InstancedVecMat4::~InstancedVecMat4() {
    glDeleteBuffers(1, &instanceVBO);
  }

  int InstancedVecMat4::getNumberOfLocationsUsed() const {
    return 4; 
  }

  std::string InstancedVecMat4::getType() const {
    return "mat4"; 
  }

  std::string InstancedVecMat4::getArrayPostfix() {
    return ""; 
  }

  const std::vector<glm::mat4>& InstancedVecMat4::getValue() const {
    return _value;
  }

  void InstancedVecMat4::setValue(const std::vector<glm::mat4>& val) {
    assert(val.size() == _size);
    _value = val;
  }

  void InstancedVecMat4::bind() {

    glEnableVertexAttribArray(getLocation()+0);
    glEnableVertexAttribArray(getLocation()+1);
    glEnableVertexAttribArray(getLocation()+2);
    glEnableVertexAttribArray(getLocation()+3);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glVertexAttribPointer(getLocation() + 0, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4 * 4, (void*)(0));
    glVertexAttribPointer(getLocation() + 1, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4 * 4, (void*)(sizeof(float) * 4));
    glVertexAttribPointer(getLocation() + 2, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4 * 4, (void*)(sizeof(float) * 8));
    glVertexAttribPointer(getLocation() + 3, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4 * 4, (void*)(sizeof(float) * 12));
    glVertexAttribDivisor(getLocation() + 0, 1);
    glVertexAttribDivisor(getLocation() + 1, 1);
    glVertexAttribDivisor(getLocation() + 2, 1);
    glVertexAttribDivisor(getLocation() + 3, 1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }
}