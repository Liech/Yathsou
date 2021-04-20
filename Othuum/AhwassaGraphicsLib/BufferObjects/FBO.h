#pragma once

#include <vector>
#include <memory>
#include <string>

namespace Ahwassa {
  class Texture;

  class FBO {
  public:
    FBO(unsigned int width, unsigned int height, const std::vector<std::string>& textureNames);
    void start();//set as rendertargets
    void end();  //unset as rendertargets
    
    std::vector<std::shared_ptr<Texture>> getUniforms();
    std::shared_ptr<Texture> getDepth();

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