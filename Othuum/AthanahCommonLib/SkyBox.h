#pragma once

#include <memory>
#include <string>

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
    SkyBox(std::string filename, std::shared_ptr<Ahwassa::Camera>);

    void draw();
  private:
    std::shared_ptr<Ahwassa::IMesh> makeCube();
    void                            makeShader();

    std::shared_ptr<Ahwassa::ShaderProgram> _shader ;
    std::shared_ptr<Ahwassa::Camera>        _camera ;
    std::shared_ptr<Ahwassa::IMesh>         _mesh   ;
    std::shared_ptr<Ahwassa::Texture>       _front ;
    std::shared_ptr<Ahwassa::Texture>       _right ;
    std::shared_ptr<Ahwassa::Texture>       _back  ;
    std::shared_ptr<Ahwassa::Texture>       _left  ;
    std::shared_ptr<Ahwassa::Texture>       _top   ;
    std::shared_ptr<Ahwassa::Texture>       _bottom;
    std::shared_ptr<Ahwassa::UniformMat4>   _mat;
  };                                        
}