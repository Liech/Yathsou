#include "VAO.h"


namespace Ahwassa {
  IVAO::IVAO(IVBO* vbo) {
    _vbo = vbo;
    glGenVertexArrays(1, &_id);
    glBindVertexArray(_id);
  }

  IVAO::~IVAO() {
    glDeleteVertexArrays(1, &_id);
  }

  unsigned int IVAO::getID() {
    return _id;
  }


  void IVAO::bind(){
    glBindVertexArray(_id);
    glDrawArrays(GL_TRIANGLES, 0, (GLsizei)_vbo->getSize());
  }

  void IVAO::init(const std::vector<AttributeDescription>& bindings){
    size_t stride = 0;
    for (int i = 0; i < bindings.size(); i++)
      stride += bindings[i].getSize();
    size_t currentOffset = 0;
    for (int i = 0; i < bindings.size(); i++) {
      AttributeDescription bind = bindings[i];
      glEnableVertexAttribArray(i);
      glBindBuffer(GL_ARRAY_BUFFER, _vbo->getID());
      glVertexAttribPointer(i, bind.getSize(), GL_FLOAT, GL_FALSE, (GLsizei)stride, (GLvoid*)currentOffset);
      currentOffset += bind.getSize();
    }

  }
}