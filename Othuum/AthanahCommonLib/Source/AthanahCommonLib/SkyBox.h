#pragma once

#include <memory>
#include <string>
#include <vector>
#include "IyathuumCoreLib/BaseTypes/MultiDimensionalArray.h"
#include "IyathuumCoreLib/BaseTypes/Color.h"

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
    SkyBox(const std::vector<unsigned char>&, std::shared_ptr<Ahwassa::Camera>);
    SkyBox(std::string filename, std::shared_ptr<Ahwassa::Camera>);
    SkyBox(std::vector<std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>>>&, std::shared_ptr<Ahwassa::Camera>);

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