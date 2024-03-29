#pragma once

#include <memory>
#include <map>
#include <vector>
#include <array>
#include <string>
#include <glm/glm.hpp>
#include <IyathuumCoreLib/BaseTypes/Color.h>
#include <AhwassaGraphicsLib/Renderer/RendererTemplate.h>
#include <AthanahCommonLib/SupCom/Gamedata/Gamedata.h>

namespace Aezesel {
  class Model3D;
}

namespace Ahwassa {
  class Camera;
  class IMesh;
  class UniformMat4;
  class UniformVec3;
  class Texture;
  class ShaderProgram;
}

namespace Athanah { 
  class Gamedata;

  class MapRenderer {
  public:
    MapRenderer(std::shared_ptr<Ahwassa::Camera> camera, std::array<std::string,5> textures, Gamedata&);
    ~MapRenderer();

    void setTextures(std::array<std::shared_ptr<Ahwassa::Texture>, 5> textures);
    void draw(Ahwassa::IMesh& mesh);
  
  private:
    std::shared_ptr<Ahwassa::Camera>                 _camera   ;
    std::unique_ptr<Ahwassa::UniformMat4>            _transform;
    std::unique_ptr<Ahwassa::UniformVec3>            _light    ;
    std::shared_ptr<Ahwassa::ShaderProgram>          _shader   ;
    std::array<std::shared_ptr<Ahwassa::Texture>, 5> _textures ;
  };
}