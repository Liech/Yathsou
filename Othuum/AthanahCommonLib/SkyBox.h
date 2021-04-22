#pragma once

#include <memory>

namespace Ahwassa {
  class Texture;
  class IMesh;
  class Camera;
  class ShaderProgram;
  class UniformMat4;
}

namespace Athanah {
  class SkyBox {
  public:
    SkyBox(std::shared_ptr<Ahwassa::Texture>, std::shared_ptr<Ahwassa::Camera>);

    void draw();
  private:
    std::shared_ptr<Ahwassa::IMesh> makeCube();
    void                            makeShader();

    std::shared_ptr<Ahwassa::ShaderProgram> _shader ;
    std::shared_ptr<Ahwassa::Camera>        _camera ;
    std::shared_ptr<Ahwassa::IMesh>         _mesh   ;
    std::shared_ptr<Ahwassa::Texture>       _texture;
    std::shared_ptr<Ahwassa::UniformMat4>   _mat;
  };                                        
}