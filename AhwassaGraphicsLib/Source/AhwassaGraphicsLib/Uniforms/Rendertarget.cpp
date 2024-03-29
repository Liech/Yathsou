#include "Rendertarget.h"

#include <stdexcept>

#include "glad/glad.h"


namespace Ahwassa {
  std::string Rendertarget::getType() const {
    return "sampler2D"; 
  }

  Rendertarget::Rendertarget(const std::string& name, const glm::ivec2& resolution) : Uniform(name) {
    _resolution = resolution;
    glGenFramebuffers(1, &_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);

    // generate texture
    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (GLsizei)_resolution[0], (GLsizei)_resolution[1], 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, 0);

    // attach it to currently bound framebuffer object
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texture, 0);

    glGenRenderbuffers(1, &_renderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _renderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, (GLsizei)_resolution[0], (GLsizei)_resolution[1]);
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
    glViewport(0, 0, (GLsizei)_resolution[0], (GLsizei)_resolution[1]);
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

  glm::ivec2 Rendertarget::getResolution() const {
    return _resolution;
  }

  void Rendertarget::setResolution(const glm::ivec2& newResolution) {
    _resolution = newResolution;
    glBindTexture(GL_TEXTURE_2D, _texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (GLsizei)_resolution[0], (GLsizei)_resolution[1], 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, _renderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, (GLsizei)_resolution[0], (GLsizei)_resolution[1]);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

  }
}