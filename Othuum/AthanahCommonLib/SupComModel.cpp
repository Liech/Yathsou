#include "SupComModel.h"

#include <filesystem>

#include "AezeselFileIOLib/SCM.h"
#include "AezeselFileIOLib/ImageIO.h"
#include "AhwassaGraphicsLib/Uniforms/Texture.h"

namespace Athanah {
  SupComModel::SupComModel(std::string unitDir, std::string unitName) {
    loadImages(unitDir,unitName);
    loadMesh(unitDir, unitName);
    loadAnimation(unitDir, unitName);
  }

  Ahwassa::Mesh<SupComVertex>& SupComModel::mesh() {
    return *_mesh;
  }

  Ahwassa::Texture& SupComModel::albedo() {
    return *_albedo;
  }

  Ahwassa::Texture& SupComModel::info() {
    return *_info;
  }

  Ahwassa::Texture& SupComModel::normal() {
    return *_normal;
  }

  void SupComModel::loadAnimation(std::string unitDir, std::string unitName) {
    std::string fullPath = unitDir + "\\" + unitName + "\\";
    for (const auto& entry : std::filesystem::directory_iterator(fullPath))
    {
      std::string animationPath = entry.path().string();
      if (animationPath.substr(animationPath.size() - 4) == ".sca")
      {
        size_t      animSeperator = animationPath.find_last_of('\\');
        std::string animationName = animationPath.substr(animSeperator + 1/*\\*/ + unitName.size() + 2/*_A*/);
        animationName = animationName.substr(0, animationName.size() - 4);
        Aezesel::SCA animLoader;
        std::shared_ptr<Aezesel::SCA::data> anim = std::make_shared<Aezesel::SCA::data>(animLoader.load(animationPath));
        _animations[animationName] = anim;
      }
    }
  }

  void SupComModel::loadMesh(std::string unitDir, std::string unitName) {
    std::string fullPath = unitDir + "\\" + unitName + "\\";
    std::string scmPath = fullPath + unitName + "_lod0.scm";
    Aezesel::SCM scm;
    _model = std::make_shared<Aezesel::SCM::data>(scm.load(scmPath));
    
    std::vector<int> indices;
    for (auto i : _model->indices) {
      indices.push_back(i.a);
      indices.push_back(i.b);
      indices.push_back(i.c);
    }
    
    std::vector<SupComVertex> vertices;
    for (auto v : _model->vertecies) {
      SupComVertex p;
      p.position= v.position;
      p.tangent = v.tangent ;
      p.normal  = v.normal  ;
      p.binormal= v.binormal;
      p.uv1     = v.uv1     ;
      p.uv2     = v.uv2     ;
      v.boneIndex[0] = p.bones[0];
      v.boneIndex[1] = p.bones[1];
      v.boneIndex[2] = p.bones[2];
      v.boneIndex[3] = p.bones[3];
      vertices.push_back(p);
    }

    _mesh = std::make_shared<Ahwassa::Mesh<SupComVertex>>(vertices,indices);
  }

  void SupComModel::loadImages(std::string unitDir, std::string unitName) {
    std::string fullPath = unitDir + "\\" + unitName + "\\";
    auto albedoArray = Aezesel::ImageIO::readImage(fullPath + "\\" + unitName + "_Albedo.dds");
    auto infoArray   = Aezesel::ImageIO::readImage(fullPath + "\\" + unitName + "_SpecTeam.dds");
    auto normalArray = Aezesel::ImageIO::readImage(fullPath + "\\" + unitName + "_normalsTS.dds");
    _albedo = std::make_shared<Ahwassa::Texture>("Albedo", albedoArray.get());
    _info   = std::make_shared<Ahwassa::Texture>("TeamSpec", infoArray.get());
    _normal = std::make_shared<Ahwassa::Texture>("Normal", normalArray.get());
  }

  std::vector<std::string> SupComModel::availableAnimations() const {
    std::vector<std::string> result;
    for (auto anim : _animations)
      result.push_back(anim.first);
    return result;
  }

  float SupComModel::getAnimationLength(const std::string& name) {
    return _animations[name]->duration;
  }

  std::vector<glm::mat4> SupComModel::getAnimation(const std::string& name, float time) {
    std::vector<glm::mat4> result;
    auto& anim = _animations[name];
    result.resize(anim->boneNames.size());
    


    for (int i = 0; i < result.size(); i++) {
      result[i] = glm::mat4(1);

    }

    return result;
  }

}