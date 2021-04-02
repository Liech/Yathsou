#include "VBO.h"


namespace Ahwassa {
  IVBO::IVBO(size_t size,size_t structsize,const void* pos) {
    _size = size;
    _structsize = structsize;
    glGenBuffers(1, &_id);
    glBindBuffer(GL_ARRAY_BUFFER, _id);
    glBufferData(GL_ARRAY_BUFFER, size * structsize, pos, GL_STATIC_DRAW);
  }

  IVBO::~IVBO(){
    glDeleteBuffers(1, &_id);
  }


  unsigned int IVBO::getID() {
    return _id;
  }

  size_t IVBO::getSize() {
    return _size;
  }
  void IVBO::setData(const void* pos, size_t size) {
    glBindBuffer(GL_ARRAY_BUFFER, _id);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size * _structsize, pos);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

}