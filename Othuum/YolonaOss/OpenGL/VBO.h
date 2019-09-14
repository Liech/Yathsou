#pragma once
#include "glad/glad.h"
#include <vector>

template<typename Struct>
class VBO
{
public:  

  VBO(std::vector<Struct> content)
  {
    _size = content.size();
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, content.size() * sizeof(Struct), content.data(), GL_STATIC_DRAW);
  }

  ~VBO()
  {
    glDeleteBuffers(1, &_vbo);
  }

  GLuint getID() {
    return _vbo;
  }

  size_t getSize() {
    return _size;
  }

private:
  GLuint _vbo;
  size_t _size;
};

