#pragma once

#include <string>
#include <memory>

#include "AezeselFileIOLib/SCM.h"
#include "AhwassaGraphicsLib/BufferObjects/Mesh.h"
#include "SupComVertex.h"

namespace Ahwassa {
  class Texture;
}

namespace Athanah {
  
  class SupComModel {
  public:
    SupComModel(std::string unitDir, std::string unitName);


    Ahwassa::Mesh<SupComVertex>& mesh();
  private:
    void loadImages(std::string unitDir, std::string unitName);
    void loadMesh  (std::string unitDir, std::string unitName);


    std::shared_ptr<Ahwassa::Texture  >          _albedo;
    std::shared_ptr<Ahwassa::Texture  >          _info  ;
    std::shared_ptr<Ahwassa::Texture  >          _normal;

    std::shared_ptr<Aezesel::SCM::data>          _model ;
    std::shared_ptr<Ahwassa::Mesh<SupComVertex>> _mesh;
  };
}