#include "Texture.h"

namespace YolonaOss {
  namespace GL {
    Texture::Texture(std::string name, MultiDimensionalArray<Color, 2> * input) : Uniform(name) {
      glGenTextures(1, &_texture);
      glBindTexture(GL_TEXTURE_2D, _texture);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (GLsizei)input->getDimension(0), (GLsizei)input->getDimension(1), 0, GL_RGBA, GL_UNSIGNED_BYTE, input->data());
      glGenerateMipmap(GL_TEXTURE_2D);
    }

    Texture::Texture(std::string name, GLuint tex) : Uniform(name) {
      _texture = tex;
    }

    Texture::~Texture() {
      glDeleteTextures(1, &_texture);
    }
    void Texture::setTextureID(GLuint tex) {
      _texture = tex;
    }

    void Texture::bind() {
      glBindTexture(GL_TEXTURE_2D, _texture);
    }
  }
}