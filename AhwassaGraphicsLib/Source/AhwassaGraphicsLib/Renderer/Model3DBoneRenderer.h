#pragma once

#include <memory>
#include <map>
#include <vector>
#include <glm/glm.hpp>
#include <AhwassaGraphicsLib/Renderer/RendererTemplate.h>

namespace Iyathuum {
  class Model3D;
}

namespace Ahwassa {
  class Camera;
  class IMesh;
  class SSBOmat4;
  class Texture;
}

namespace Ahwassa {
  class Model3DBoneRenderer {
  public:
    Model3DBoneRenderer(std::shared_ptr<Ahwassa::Camera> camera);
    virtual ~Model3DBoneRenderer();

    void draw(Iyathuum::Model3D&);

  private:
  };
}