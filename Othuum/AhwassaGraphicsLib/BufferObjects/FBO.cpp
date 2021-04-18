#include "FBO.h"

#include <stdexcept>

#include "glad/glad.h"

#include "AhwassaGraphicsLib/Uniforms/Texture.h"

//https://learnopengl.com/Advanced-Lighting/Deferred-Shading

namespace Ahwassa {
  FBO::FBO(unsigned int width,unsigned int height, const std::vector<std::string>& textureNames){
    _width = width;
    _height = height;
    
    glGenFramebuffers(1, &_id);
    glBindFramebuffer(GL_FRAMEBUFFER, _id);


    _textures.resize(textureNames.size());
    for (int i = 0; i < textureNames.size(); i++) {
      std::shared_ptr<Texture> texture = std::make_shared<Texture>(textureNames[i],_width,_height);
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

    glDrawBuffers(3, forFrameBufferGL_COLOR_ATTACHMENT.data());

    // create and attach depth buffer (renderbuffer)
    glGenRenderbuffers(1, &_depth);
    glBindRenderbuffer(GL_RENDERBUFFER, _depth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, _width, _height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depth);


    // finally check if framebuffer is complete
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
      throw std::runtime_error("Framebuffer not complete!");
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }

  unsigned int FBO::getGL_COLOR_ATTACHMENT(int number) {
    return GL_COLOR_ATTACHMENT0 + number;
  }

  unsigned int FBO::getGL_TEXTURE(int number) {
    return GL_TEXTURE0 + number;
  }

  void FBO::start() {
    _oldViewPort.resize(4);
    glGetIntegeri_v(GL_VIEWPORT, 0, _oldViewPort.data());
    glViewport(0, 0, (GLsizei)_width, (GLsizei)_height);
    glBindFramebuffer(GL_FRAMEBUFFER, _id);
    glClearColor(0,0,0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
  }

  void FBO::end() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
    glViewport(_oldViewPort[0], _oldViewPort[1], _oldViewPort[2], _oldViewPort[3]);
  }

  std::vector<std::shared_ptr<Texture>> FBO::getUniforms() {
    return _textures;
  }
}