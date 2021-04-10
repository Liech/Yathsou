#include "IBO.h"

#include "glad/glad.h"
#include "VAO.h"

namespace Ahwassa {
  IBO::IBO(const std::vector<int>& content)
  {
    _size = content.size();
    glGenBuffers(1, &_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, content.size() * sizeof(unsigned int), content.data(), GL_STATIC_DRAW);
  }

  IBO::~IBO()
  {
    glDeleteBuffers(1, &_ibo);
  }

  unsigned int IBO::getID() {
    return _ibo;
  }

  size_t IBO::getSize() {
    return _size;
  }

  void IBO::drawInstanced(VAO* vertexBuffer,size_t amount) {
    glBindVertexArray(vertexBuffer->getID());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
    
    glDrawElementsInstanced(GL_TRIANGLES, (GLsizei)_size, GL_UNSIGNED_INT, 0, amount);    
  }

  void IBO::draw(VAO* vertexBuffer) {
    glBindVertexArray(vertexBuffer->getID());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);

    // Draw the triangles !
    glDrawElements(
      GL_TRIANGLES,      // mode
      (GLsizei)_size,    // count
      GL_UNSIGNED_INT,   // type
      (void*)0           // element array buffer offset
    );
  }
}

