#include "SupCom/SupComModel.h"

#include <filesystem>
#include <fstream>
#include <set>

#include "AezeselFileIOLib/SupremeCommander/SCD.h"
#include "AezeselFileIOLib/SupremeCommander/SCM.h"
#include "AezeselFileIOLib/ImageIO.h"
#include "AezeselFileIOLib/SupremeCommander/SupremeCommanderAnimator.h"

#include "AhwassaGraphicsLib/Uniforms/Texture.h"

namespace Athanah {
  SupComModel::SupComModel(const std::string& unitDir, const std::string& unitName) {
    Aezesel::SCD archive(unitDir);
    load(archive, unitName);
  }

  SupComModel::SupComModel(Aezesel::SCD& archive, const std::string& unitName) {
    load(archive, unitName);
  }

  void SupComModel::load(Aezesel::SCD& archive, const std::string& unitName) {
    std::cout << "---Loading: " << unitName << "---" << std::endl;
    Aezesel::SCM scm;
    _model = std::make_shared<Aezesel::SCM::data>(scm.load(archive.loadBinaryFile(unitName + "/" + unitName + "_lod0.scm")));
    loadMesh();
    loadImages(archive, unitName);
    loadAnimation(archive, unitName);
  }

  void SupComModel::loadAnimation(Aezesel::SCD& archive, const std::string& unitName) {
    for (const auto& entry : archive.getDirectories(unitName))
    {
      if (entry.ends_with(".sca"))
      {
        size_t      animSeperator = entry.find_last_of('\\');
        std::string animationName = entry.substr(animSeperator + 1/*\\*/ + unitName.size() + 2/*_A*/);
        std::cout << "Loading Animation: " << animationName << std::endl;
        animationName = animationName.substr(0, animationName.size() - 4);
        Aezesel::SCA animLoader;
        std::shared_ptr<Aezesel::SCA::data> anim = std::make_shared<Aezesel::SCA::data>(animLoader.load(archive.loadBinaryFile(entry)));
        _animations[animationName] = anim;

        std::cout << animationName << std::endl;
        std::set<std::string> keyflags;
        for (int i = 0; i < anim->animation.size(); i++)
          keyflags.insert(anim->animation[i].flag2str());
        _animator[animationName] = std::make_shared<Aezesel::SupremeCommanderAnimator>(*anim, *_model);
      }
    }
  }

  void SupComModel::loadImages(Aezesel::SCD& archive, const std::string& unitName) {
    std::string albedo = unitName + "/" + unitName + "_Albedo.dds";
    if (archive.fileExists(albedo)) {
      auto albedoArray = Aezesel::ImageIO::readImage(Aezesel::ImageIO::Format::DDS, archive.loadBinaryFile(albedo));
      _albedo = std::make_shared<Ahwassa::Texture>("Albedo", albedoArray.get());
    }
    else
      _albedo = std::make_shared<Ahwassa::Texture>("Albedo", 0);

    std::string specTeam = unitName + "/" + unitName + "_SpecTeam.dds";
    if (archive.fileExists(specTeam)) {
      auto infoArray = Aezesel::ImageIO::readImage(Aezesel::ImageIO::Format::DDS, archive.loadBinaryFile(specTeam));
      _info = std::make_shared<Ahwassa::Texture>("TeamSpec", infoArray.get());
    }
    else
      _info = std::make_shared<Ahwassa::Texture>("TeamSpec", 0);

    std::string normal = unitName + "/" + unitName + "_normalsTS.dds";
    if (archive.fileExists(normal)) {
      auto normalArray = Aezesel::ImageIO::readImage(Aezesel::ImageIO::Format::DDS, archive.loadBinaryFile(normal));
      _normal = std::make_shared<Ahwassa::Texture>("Normal", normalArray.get());
    }
    else
      _normal = std::make_shared<Ahwassa::Texture>("Normal", 0);

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

  Aezesel::SCM::data& SupComModel::scm() {
    return *_model;
  }

  void SupComModel::loadMesh() {
    std::cout << "Loading: " << "Mesh" << std::endl;
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
      p.bone = v.boneIndex[0];
      vertices.push_back(p);
    }

    _mesh = std::make_shared<Ahwassa::Mesh<SupComVertex>>(vertices,indices);
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

  glm::vec3 SupComModel::getTranslationVector(glm::mat4 mat) {
    return glm::vec3(mat[3].x,mat[3].y,mat[3].z);
  }

  std::vector<glm::mat4> SupComModel::getAnimation(const std::string& name, float time) {
    return _animator[name]->getMatrices(time);
  }
}