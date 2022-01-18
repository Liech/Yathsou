#pragma once

#include "AhwassaGraphicsLib/Uniforms/Uniform.h"

namespace Ahwassa {
  class Rendertarget : public Uniform {
  public:
    Rendertarget(std::string name, size_t nX, size_t nY);
    virtual ~Rendertarget();

    void start();
    void end();
    void bind() override;
    virtual std::string getType() override;
    unsigned int getTextureID() { return _texture; }

    glm::ivec2 getResolution();

  private:
    unsigned int _texture      = 0;
    unsigned int _framebuffer  = 0;
    unsigned int _renderbuffer = 0;

    size_t _nX = 0;
    size_t _nY = 0;

    std::vector<int> _oldViewPort;
  };
}