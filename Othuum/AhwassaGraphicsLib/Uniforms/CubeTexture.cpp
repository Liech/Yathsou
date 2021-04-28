#include "CubeTexture.h"

#include "glad/glad.h"


namespace Ahwassa {
  CubeTexture::CubeTexture(const std::string& name, std::vector<std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>>>& input) : Uniform(name) {
    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _texture);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, (GLsizei)input[0]->getDimension(0), (GLsizei)input[0]->getDimension(1), 0, GL_RGBA, GL_UNSIGNED_BYTE, input[0]->data());
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, (GLsizei)input[1]->getDimension(0), (GLsizei)input[1]->getDimension(1), 0, GL_RGBA, GL_UNSIGNED_BYTE, input[1]->data());
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, (GLsizei)input[2]->getDimension(0), (GLsizei)input[2]->getDimension(1), 0, GL_RGBA, GL_UNSIGNED_BYTE, input[2]->data());
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, (GLsizei)input[3]->getDimension(0), (GLsizei)input[3]->getDimension(1), 0, GL_RGBA, GL_UNSIGNED_BYTE, input[3]->data());
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, (GLsizei)input[4]->getDimension(0), (GLsizei)input[4]->getDimension(1), 0, GL_RGBA, GL_UNSIGNED_BYTE, input[4]->data());
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, (GLsizei)input[5]->getDimension(0), (GLsizei)input[5]->getDimension(1), 0, GL_RGBA, GL_UNSIGNED_BYTE, input[5]->data());

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
  }

  CubeTexture::CubeTexture(const std::string& name, int width, int height) : Uniform(name) {
    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _texture);
    glTexImage2D(GL_TEXTURE_CUBE_MAP, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
  }

  CubeTexture::CubeTexture(const std::string& name, unsigned int tex, CubeTextureReleaseBehavior released) : Uniform(name) {
    _texture = tex;
    if (CubeTextureReleaseBehavior::KeepTextureOnDeconstructor == released)
      release();
  }

  CubeTexture::~CubeTexture() {
    if (!_released)
      glDeleteTextures(1, &_texture);
  }

  bool CubeTexture::isTexture() {
    return true; 
  }

  std::string CubeTexture::getType() {
    return "samplerCube";
  }

  unsigned int CubeTexture::getTextureID() const {
    return _texture;
  }

  void CubeTexture::release()
  {
    _released = true;
  }

  void CubeTexture::setTextureID(unsigned int tex) {
    _texture = tex;
  }


  void CubeTexture::bind() {
    int loc = getTextureLocation();
    glActiveTexture(GL_TEXTURE0 + loc);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _texture);
    glUniform1i(getLocation(), loc);
  }
}