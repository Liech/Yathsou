#include "InstancedVecMat4.h"

#include "IyathuumCoreLib/lib/glm/gtc/type_ptr.hpp"
#include "glad/glad.h"

namespace Ahwassa {
  InstancedVecMat4::InstancedVecMat4(std::string name, int size) : Uniform(name) { 
    _value.resize(size); 
    _size = size; 

    glGenBuffers(1, &instanceVBO);
  }

  InstancedVecMat4::~InstancedVecMat4() {
    glDeleteBuffers(1, &instanceVBO);
  }

  int InstancedVecMat4::getNumberOfLocationsUsed(){
    return 4; 
  }

  std::string InstancedVecMat4::getType() {
    return "mat4"; 
  }

  std::string InstancedVecMat4::getArrayPostfix() {
    return ""; 
  }

  const std::vector<glm::mat4>& InstancedVecMat4::getValue() {
    return _value;
  }

  void InstancedVecMat4::setValue(const std::vector<glm::mat4>& val) {
    assert(val.size() == _size);
    _value = val;
  }

  void InstancedVecMat4::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * _value.size(), _value.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

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