#pragma once

#include "AhwassaGraphicsLib/Uniforms/Uniform.h"

namespace Ahwassa {
  class Rendertarget : public Uniform {
  public:
    Rendertarget(std::string name, const glm::ivec2& resolution);
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

    glm::ivec2       _resolution;
    std::vector<int> _oldViewPort;
  };
}