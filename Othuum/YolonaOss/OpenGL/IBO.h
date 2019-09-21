#pragma once
#include "glad/glad.h"
#include <vector>
#include "VAO.h"
namespace YolonaOss {
  namespace GL {
    class IBO
    {
    public:

      IBO(std::vector<GLuint>& content)
      {
        _size = content.size();
        glGenBuffers(1, &_ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, content.size() * sizeof(unsigned int), content.data(), GL_STATIC_DRAW);
      }

      ~IBO()
      {
        glDeleteBuffers(1, &_ibo);
      }

      GLuint getID() {
        return _ibo;
      }

      size_t getSize() {
        return _size;
      }

      void bind(VAO_I* vertexBuffer) {
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

    private:
      GLuint _ibo;
      size_t _size;
    };
  }
}
