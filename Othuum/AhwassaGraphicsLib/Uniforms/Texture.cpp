#include "Texture.h"

#include "glad/glad.h"


namespace Ahwassa {
  Texture::Texture(std::string name, Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2> * input) : Uniform(name) {
    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)input->getDimension(0), (GLsizei)input->getDimension(1), 0, GL_RGBA, GL_UNSIGNED_BYTE, input->data());
    glGenerateMipmap(GL_TEXTURE_2D);
  }

  Texture::Texture(std::string name, int width, int height) : Uniform(name) {
    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
  }

  Texture::Texture(std::string name, unsigned int tex, ReleaseBehavior released) : Uniform(name) {
    _texture = tex;
    if (ReleaseBehavior::KeepTextureOnDeconstructor == released)
      release();
  }

  Texture::~Texture() {
    if (!_released)
      glDeleteTextures(1, &_texture);
  }

  bool Texture::isTexture() {
    return true; 
  }

  std::string Texture::getType() {
    return "sampler2D"; 
  }

  unsigned int Texture::getTextureID() const {
    return _texture;
  }

  void Texture::release()
  {
    _released = true;
  }

  void Texture::setTextureID(unsigned int tex) {
    _texture = tex;
  }

  void Texture::bind() {
    int loc = getTextureLocation();
    glActiveTexture(GL_TEXTURE0 + loc);
    glBindTexture(GL_TEXTURE_2D, _texture);
    glUniform1i(getLocation(), loc);
  }
}