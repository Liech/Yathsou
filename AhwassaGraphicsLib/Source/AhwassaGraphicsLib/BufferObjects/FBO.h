#pragma once

#include <vector>
#include <memory>
#include <string>
#include "AhwassaGraphicsLib/Uniforms/Texture.h"

namespace Ahwassa {
  class FBO {
  public:
    FBO(unsigned int width, unsigned int height, const std::vector<std::string>& textureNames, const std::vector<TextureFormat>& formats);
    void start();//set as rendertargets
    void end();  //unset as rendertargets
    
    std::vector<std::shared_ptr<Texture>> getUniforms();
    std::shared_ptr<Texture> getDepth();
    unsigned int getID();

  private:
    unsigned int getGL_COLOR_ATTACHMENT(int number);
    unsigned int getGL_TEXTURE(int number);

    unsigned int _width;
    unsigned int _height;
    unsigned int _id;

    std::shared_ptr<Texture>              _depth;
    std::vector<std::shared_ptr<Texture>> _textures;
    std::vector<int>                      _oldViewPort;
  };
}