#pragma once

#include <memory>
#include <vector>

namespace Ahwassa {
  class FBO;
  class Texture;

  class DeferredComposer {
  public:
    DeferredComposer(int width, int height);
    void start();
    void end();
    std::vector<std::shared_ptr<Texture>> getRawTextures();
  private:
    
    std::shared_ptr<Ahwassa::FBO> _fbo;
  };
}