#include "Rendertarget.h"

#include <stdexcept>

#include "glad/glad.h"


namespace Ahwassa {
  std::string Rendertarget::getType() {
    return "sampler2D"; 
  }

  Rendertarget::Rendertarget(std::string name, size_t nX, size_t nY) : Uniform(name) {
    _nX = nX;
    _nY = nY;
    glGenFramebuffers(1, &_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);

    // generate texture
    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (GLsizei)nX, (GLsizei)nY, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    // attach it to currently bound framebuffer object
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texture, 0);

    glGenRenderbuffers(1, &_renderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _renderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, (GLsizei)nX, (GLsizei)nY);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _renderbuffer);


    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
      throw std::runtime_error("Framebuffer error");
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }

  Rendertarget::~Rendertarget() {
    glDeleteTextures(1, &_texture);
  }

  void Rendertarget::start() {
    
    _oldViewPort.resize(4);
    glGetIntegeri_v(GL_VIEWPORT, 0, _oldViewPort.data());
    glViewport(0, 0, (GLsizei)_nX, (GLsizei)_nY);
    glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
  }

  void Rendertarget::end() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
    glViewport(_oldViewPort[0], _oldViewPort[1], _oldViewPort[2], _oldViewPort[3]);
  }

  void Rendertarget::bind() {
    glBindTexture(GL_TEXTURE_2D, _texture);
  }
}