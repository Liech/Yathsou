#include "Texture.h"

#include "glad/glad.h"


namespace Ahwassa {
  Texture::Texture(const std::string& name, Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>* input, TextureFormat format) : Uniform(name) {
    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);
    int f = GL_RGBA;
    if (format == TextureFormat::RGBA32)
      f = GL_RGBA32F;

    glTexImage2D(GL_TEXTURE_2D, 0, f, (GLsizei)input->getDimension(0), (GLsizei)input->getDimension(1), 0, GL_RGBA, GL_UNSIGNED_BYTE, input->data());
    glGenerateMipmap(GL_TEXTURE_2D);
  }

  Texture::Texture(const std::string& name, int width, int height, TextureFormat format) : Uniform(name) {
    int f = GL_RGBA;
    if (format == TextureFormat::RGBA32)
      f = GL_RGBA32F;
    
    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
  }

  Texture::Texture(const std::string& name, unsigned int tex, ReleaseBehavior released) : Uniform(name) {
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

  std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>> Texture::getImage() {
    int w, h;
    int miplevel = 0;
    glBindTexture(GL_TEXTURE_2D, _texture);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_WIDTH, &w);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_HEIGHT, &h);


    GLuint fbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texture, 0);

    int data_size = w * h * 4;
    std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>> result = std::make_unique< Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>>(w, h);
    glReadPixels(0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, result->data());

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDeleteFramebuffers(1, &fbo);
    
    return std::move(result);
  }

}