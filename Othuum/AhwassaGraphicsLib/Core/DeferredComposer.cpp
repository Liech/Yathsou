#include "DeferredComposer.h"

#include <vector>
#include <string>

#include "BufferObjects/FBO.h"

namespace Ahwassa {
  DeferredComposer::DeferredComposer(int width, int height) {
    _fbo = std::make_shared<Ahwassa::FBO>(width,height, std::vector<std::string> {"gPosition", "gNormal", "gAlbedoSpec"});

  }

  void DeferredComposer::start() {
    _fbo->start();
  }

  void DeferredComposer::end() {
    _fbo->end();
  }

  std::vector<std::shared_ptr<Texture>> DeferredComposer::getRawTextures() {
    return _fbo->getUniforms();
  }

}