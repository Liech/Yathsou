#include "Texture.h"


Texture::Texture(std::string name, MultiDimensionalArray<Color, 2>* input) : Uniform(name) {
  glGenTextures(1, &_texture);
  glBindTexture(GL_TEXTURE_2D, _texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, input->getDimension(0), input->getDimension(1), 0, GL_RGBA, GL_UNSIGNED_BYTE, input->data());
  glGenerateMipmap(GL_TEXTURE_2D);
}

Texture::~Texture() {
  glDeleteTextures(1, &_texture);
}

void Texture::bind() {
  //glActiveTexture(GL_TEXTURE0 + _texture);
  glBindTexture(GL_TEXTURE_2D, _texture);
  //glBindSampler(getLocation(), _texture);
}
