#include "VAO.h"

#include "glad/glad.h"
#include "Core/AttributeDescription.h"

namespace Ahwassa {
  VAO::VAO(IVBO* vbo) {
    _vbo = { vbo };
    glGenVertexArrays(1, &_id);
    glBindVertexArray(_id);
    _size = vbo->getSize();

    init({vbo->getBinding()});
  }

  VAO::VAO(std::vector<IVBO*> vbo) {
    _vbo = vbo;
    glGenVertexArrays(1, &_id);
    glBindVertexArray(_id);
    _size = 0;
    std::vector<std::vector<AttributeDescription>> bindings;
    for (int i = 0; i < vbo.size(); i++) {
      bindings.push_back(vbo[i]->getBinding());
      _size += _vbo[i]->getSize();
    }

    init(bindings);
  }

  VAO::~VAO() {
    glDeleteVertexArrays(1, &_id);
  }

  unsigned int VAO::getID() {
    return _id;
  }


  void VAO::draw() const{
    glBindVertexArray(_id);
    glDrawArrays(GL_TRIANGLES, 0, (GLsizei)_size);
  }

  void VAO::drawInstanced(size_t amount) const {
    glBindVertexArray(_id);
    glDrawArraysInstanced(GL_TRIANGLES, 0, (GLsizei)_size, amount);
  }

  void VAO::init(const std::vector<std::vector<AttributeDescription>>& bindingCollection){
    for (int current = 0; current < bindingCollection.size(); current++) {
      auto& bindings = bindingCollection[current];
      size_t stride = 0;
      for (int i = 0; i < bindings.size(); i++)
        stride += bindings[i].getSize();
      size_t currentOffset = 0;
      for (int i = 0; i < bindings.size(); i++) {
        const AttributeDescription& bind = bindings[i];
        glEnableVertexAttribArray(i);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo[current]->getID());
        glVertexAttribPointer(i, (GLint)bind.getSizeOf(), (GLenum)bind.getType(), GL_FALSE, (GLsizei)stride, (GLvoid*)currentOffset);
        if (bind.isInstancing())
          glVertexAttribDivisor(i, 1);
        currentOffset += bind.getSize();
      }
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }
}