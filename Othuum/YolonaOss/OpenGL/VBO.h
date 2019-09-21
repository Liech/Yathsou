#pragma once
#include "glad/glad.h"
#include <vector>
namespace YolonaOss {
  namespace GL {
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

      void setData(std::vector<Struct> content) {
        if (_size != content.size())
          throw std::runtime_error("Size different");

        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, content.size() * sizeof(Struct), content.data());
        glBindBuffer(GL_ARRAY_BUFFER, 0);

      }

    private:
      GLuint _vbo;
      size_t _size;
    };
  }
}
