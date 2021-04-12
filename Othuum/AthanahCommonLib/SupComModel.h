#pragma once

#include <string>
#include <memory>

#include "AezeselFileIOLib/SCM.h"
#include "AezeselFileIOLib/SCA.h"
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
    Ahwassa::Texture& albedo();
    Ahwassa::Texture& info  ();
    Ahwassa::Texture& normal();

    std::vector<std::string> availableAnimations() const;
    float                    getAnimationLength(const std::string& name);
    std::vector<glm::mat4>   getAnimation(const std::string& name, float time);
    std::vector<glm::mat4>   wargh(const std::string& name, float time);

  private:
    void loadImages    (std::string unitDir, std::string unitName);
    void loadMesh      (std::string unitDir, std::string unitName);
    void loadAnimation (std::string unitDir, std::string unitName);

    glm::vec3 getTranslationVector(glm::mat4);

    std::shared_ptr<Ahwassa::Texture> _albedo = nullptr;
    std::shared_ptr<Ahwassa::Texture> _info   = nullptr;
    std::shared_ptr<Ahwassa::Texture> _normal = nullptr;

    std::shared_ptr<Aezesel::SCM::data>                       _model;
    std::map<std::string,std::shared_ptr<Aezesel::SCA::data>> _animations;
    std::shared_ptr<Ahwassa::Mesh<SupComVertex>>              _mesh;
  };
}