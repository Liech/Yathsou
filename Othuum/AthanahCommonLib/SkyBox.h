#pragma once

#include <memory>
#include <string>
#include <vector>

namespace Ahwassa {
  class UniformVecTexture;
  class Texture;
  class IMesh;
  class Camera;
  class ShaderProgram;
  class UniformMat4;
}

namespace Athanah {
  class SkyBox {
  public:
    SkyBox(std::string filename, std::shared_ptr<Ahwassa::Camera>);

    void draw();
  private:
    std::shared_ptr<Ahwassa::IMesh> makeCube();
    void                            makeShader();

    std::shared_ptr<Ahwassa::ShaderProgram>          _shader ;
    std::shared_ptr<Ahwassa::Camera>                 _camera ;
    std::shared_ptr<Ahwassa::IMesh>                  _mesh   ;
    std::vector < std::shared_ptr<Ahwassa::Texture>> _textureArray;
    std::shared_ptr<Ahwassa::UniformVecTexture>      _textures;
    std::shared_ptr<Ahwassa::UniformMat4>            _mat;
  };                                        
}