#pragma once

#include <string>
#include <memory>
#include <map>
#include <vector>

#include "AezeselFileIOLib/SupremeCommander/SCM.h"
#include "AezeselFileIOLib/SupremeCommander/SCA.h"
#include "AhwassaGraphicsLib/BufferObjects/Mesh.h"
#include "SupComVertex.h"

namespace Ahwassa {
  class Texture;
}
namespace Aezesel {
  class SupremeCommanderAnimator;
}

namespace Athanah {
  class SupComModel {
  public:
    SupComModel(const std::string& unitDir, const std::string& unitName);
    SupComModel(const std::string& unitName, const std::map<std::string, std::vector<unsigned char>>& folder);


    Ahwassa::Mesh<SupComVertex>& mesh();
    Ahwassa::Texture&            albedo();
    Ahwassa::Texture&            info  ();
    Ahwassa::Texture&            normal();
    Aezesel::SCM::data&          scm();

    std::vector<std::string> availableAnimations() const;
    float                    getAnimationLength(const std::string& name);
    std::vector<glm::mat4>   getAnimation(const std::string& name, float time);

  private:
    void loadImages    (const std::string& unitName, const std::map<std::string, std::vector<unsigned char>>& folder);
    void loadImages    (const std::string& unitDir, const std::string& unitName);
    void loadMesh      ();
    void loadAnimation (std::string unitDir, std::string unitName);

    glm::vec3 getTranslationVector(glm::mat4);

    std::shared_ptr<Ahwassa::Texture> _albedo = nullptr;
    std::shared_ptr<Ahwassa::Texture> _info   = nullptr;
    std::shared_ptr<Ahwassa::Texture> _normal = nullptr;

    std::shared_ptr<Aezesel::SCM::data>                                       _model;
    std::map<std::string, std::shared_ptr<Aezesel::SCA::data>>                _animations;
    std::map<std::string, std::shared_ptr<Aezesel::SupremeCommanderAnimator>> _animator;
    std::shared_ptr<Ahwassa::Mesh<SupComVertex>>                              _mesh;
  };
}