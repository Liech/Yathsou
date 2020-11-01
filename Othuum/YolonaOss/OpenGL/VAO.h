#pragma once

#include "VBO.h"
#include "AttributeDescription.h"
namespace YolonaOss {
  namespace GL {
    class VAO_I {
    public:
      virtual void bind() = 0;
      virtual GLuint getID() = 0;
    };

    template<typename Struct>
    class VAO : public VAO_I
    {
    public:
      VAO(VBO<Struct>* vbo) {
        _vbo = vbo;
        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);

        Struct s;
        std::vector<AttributeDescription> bindings = s.getBinding();
        size_t stride = 0;
        for (int i = 0; i < bindings.size(); i++)
          stride += bindings[i].getSize();
        size_t currentOffset = 0;
        for (int i = 0; i < bindings.size(); i++) {
          AttributeDescription bind = bindings[i];
          glEnableVertexAttribArray(i);
          glBindBuffer(GL_ARRAY_BUFFER, vbo->getID());
          glVertexAttribPointer(i, bind.size, GL_FLOAT, GL_FALSE, (GLsizei)stride, (GLvoid*)currentOffset);
          currentOffset += bind.getSize();
        }
      }

      ~VAO() {
        glDeleteVertexArrays(1, &_vao);
      }

      void bind() override {
        glBindVertexArray(_vao);
        glDrawArrays(GL_TRIANGLES, 0, (GLsizei)_vbo->getSize());
      }

      GLuint getID() override {
        return _vao;
      }

    private:
      VBO<Struct>* _vbo;
      GLuint       _vao;
    };
  }
}
