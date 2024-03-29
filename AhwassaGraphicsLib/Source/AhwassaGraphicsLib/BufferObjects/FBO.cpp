#include "FBO.h"

#include <stdexcept>

#include "glad/glad.h"


//https://learnopengl.com/Advanced-Lighting/Deferred-Shading

namespace Ahwassa {
  FBO::FBO(const glm::ivec2& resolution, const std::vector<std::string>& textureNames, const std::vector<TextureFormat>& formats){
    _resolution = resolution;
    
    glGenFramebuffers(1, &_id);
    glBindFramebuffer(GL_FRAMEBUFFER, _id);

    _textures.resize(textureNames.size());
    for (int i = 0; i < textureNames.size(); i++) {
      std::shared_ptr<Texture> texture = std::make_shared<Texture>(textureNames[i],_resolution, formats[i]);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glFramebufferTexture2D(GL_FRAMEBUFFER, getGL_COLOR_ATTACHMENT(i), GL_TEXTURE_2D, texture->getTextureID(), 0);
      _textures[i] = texture;
      glBindTexture(GL_TEXTURE_2D, 0);
    }

    std::vector<unsigned int> forFrameBufferGL_COLOR_ATTACHMENT;
    forFrameBufferGL_COLOR_ATTACHMENT.resize(_textures.size());
    for (int i = 0; i < _textures.size(); i++)
      forFrameBufferGL_COLOR_ATTACHMENT[i] = getGL_COLOR_ATTACHMENT(i);

    glDrawBuffers(_textures.size(), forFrameBufferGL_COLOR_ATTACHMENT.data());

    initDepthBuffer();

    auto status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    // finally check if framebuffer is complete
    if (status != GL_FRAMEBUFFER_COMPLETE)
      throw std::runtime_error("Framebuffer not complete!");
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }

  FBO::~FBO() {
    glDeleteTextures(1, &_id);
  }

  unsigned int FBO::getGL_COLOR_ATTACHMENT(int number) const {
    return GL_COLOR_ATTACHMENT0 + number;
  }

  unsigned int FBO::getGL_TEXTURE(int number) const {
    return GL_TEXTURE0 + number;
  }

  void FBO::start() {
    _oldViewPort.resize(4);
    glGetIntegeri_v(GL_VIEWPORT, 0, _oldViewPort.data());
    glViewport(0, 0, (GLsizei)_resolution[0], (GLsizei)_resolution[1]);
    glBindFramebuffer(GL_FRAMEBUFFER, _id);
    glClearColor(0,0,0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
  }

  void FBO::end() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
    glViewport(_oldViewPort[0], _oldViewPort[1], _oldViewPort[2], _oldViewPort[3]);
  }

  std::vector<std::shared_ptr<Texture>> FBO::getUniforms() const{
    return _textures;
  }

  std::shared_ptr<Texture> FBO::getDepth() const {
    return _depth;
  }

  unsigned int FBO::getID() const{
    return _id;
  }

  void FBO::initDepthBuffer() {
    unsigned int d;
    glGenTextures(1, &d);
    if (d == -1)
      throw std::runtime_error("Error in creating texture");
    glBindTexture(GL_TEXTURE_2D, d);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, _resolution[0], _resolution[1], 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, d, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    if (_depth)
      _depth->setTextureID(d);
    else
      _depth = std::make_shared<Texture>("DepthBuffer", d, ReleaseBehavior::DeleteOnDeconstructor);

  }

  void FBO::setResolution(const glm::ivec2& resolution) {
    _resolution = resolution;

    glBindFramebuffer(GL_FRAMEBUFFER, _id);
    initDepthBuffer();

    for (int i = 0; i < _textures.size(); i++) {
      std::shared_ptr<Texture> texture = std::make_shared<Texture>(_textures[i]->getName(), _resolution, _textures[i]->getFormat());
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glFramebufferTexture2D(GL_FRAMEBUFFER, getGL_COLOR_ATTACHMENT(i), GL_TEXTURE_2D, texture->getTextureID(), 0);
      glBindTexture(GL_TEXTURE_2D, 0);
      _textures[i]->setTextureID(texture->getTextureID());
      texture->release();
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }
}