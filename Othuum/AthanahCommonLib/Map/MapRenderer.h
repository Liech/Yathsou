#pragma once

#include <memory>
#include <map>
#include <vector>
#include "IyathuumCoreLib/lib/glm/glm.hpp"
#include "AhwassaGraphicsLib/Renderer/RendererTemplate.h"

namespace Aezesel {
  class Model3D;
}

namespace Ahwassa {
  class Camera;
  class IMesh;
  class UniformMat4;
  class UniformVec3;
  class Texture;
}

namespace Athanah {
  struct MapRendererMesh {
    glm::mat4       transformation;
    Iyathuum::Color color;
  };
  
  class MapRenderer {
  public:
    MapRenderer(std::shared_ptr<Ahwassa::Camera> camera);
    ~MapRenderer();

    void draw(std::shared_ptr<Ahwassa::IMesh> mesh);
  
  private:
    std::shared_ptr<Ahwassa::Camera> _camera;
  };
}