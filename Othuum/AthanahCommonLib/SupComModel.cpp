#include "SupComModel.h"

#include <filesystem>
#include <fstream>
#include <filesystem>
#include <set>

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

        std::cout << animationName << std::endl;
        std::set<std::string> keyflags;
        for (int i = 0; i < anim->animation.size(); i++)
          keyflags.insert(anim->animation[i].flag2str());
        for (auto x : keyflags)
          std::cout << "    Keyflag: " << x << std::endl;

        prepareAnimationHelper(animationName);
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
      p.bone = v.boneIndex[0];
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
    _info = std::make_shared<Ahwassa::Texture>("TeamSpec", infoArray.get());
    _normal = std::make_shared<Ahwassa::Texture>("Normal", normalArray.get());
    
    //_albedo = std::make_shared<Ahwassa::Texture>("Albedo", 0);
    //_info = std::make_shared<Ahwassa::Texture>("TeamSpec", 0);
    //_normal = std::make_shared<Ahwassa::Texture>("Normal", 0);
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

  void SupComModel::prepareAnimationHelper(std::string animationName) {
    _animationHelper[animationName] = animationHelper();
    animationHelper& result = _animationHelper[animationName];
     
    result.inverse.resize(_model->bones.size());
    result.forward.resize(_model->bones.size());
    for (int i = 0; i < result.inverse.size(); i++) {
      result.inverse[i] = _model->bones[i].relativeInverseMatrix;
      result.forward[i] = glm::inverse(_model->bones[i].relativeInverseMatrix);
    }

    for (int i = 0; i < _model->bones.size(); i++) {
      std::vector<int> chain;
      chain.push_back(i);

      while (_model->bones[chain.back()].parentIndex != -1)
        chain.push_back(_model->bones[chain.back()].parentIndex);
      result.parentChain.push_back(chain);
    }

    auto& anim = _animations[animationName];
    std::map<std::string, int> preMap;
    for (int i = 0; i < anim->boneNames.size(); i++)
      preMap[anim->boneNames[i]] = i;
    for (int i = 0; i < _model->boneNames.size(); i++)
    {
      if (preMap.count(_model->bones[i].name) != 0)
        result.animMap[i] = preMap[_model->bones[i].name] + 1;
      else
        result.animMap[i] = 0;
    }
  }

  std::vector<glm::mat4> SupComModel::getAnimation(const std::string& name, float time) {
    //this function is not really fast. But somewhat correct.
    //faster things could be developed based on this.

    animationHelper&               helper     = _animationHelper[name];
    std::map<int, int>&            animMap    = helper.animMap;
    std::vector<glm::mat4>&        inverse    = helper.inverse;
    std::vector<glm::mat4>&        forward    = helper.forward;
    std::vector<std::vector<int>>& parentChain= helper.parentChain;
    
    auto& anim = _animations[name];
    int frameno = (int)((time / anim->duration) * (anim->animation.size() - 1)) + 1;
    Aezesel::SCA::frame& frame = anim->animation[frameno];

    std::vector<glm::mat4> rotation;
    rotation.resize(frame.bones.size());
    for (int i = 0; i < frame.bones.size(); i++)
    {
      glm::quat iden = glm::identity<glm::quat>();
      glm::quat rot = glm::normalize(frame.bones[i].rotation);
      glm::mat4 sub = Aezesel::SCA::QuatToMat(rot);
      rotation[i] = sub;
    }

    std::vector<glm::mat4> translation;
    translation.resize(frame.bones.size());
    for (int i = 0; i < frame.bones.size(); i++)
    {
      glm::mat4 sub = glm::mat4(1.0);
      sub = glm::translate(sub, frame.bones[i].position);
      translation[i] = sub;
    }

    auto r = [&](int x) {
      if (rotation.size() <= x)
        return glm::mat4(1);
      if (animMap[x] >= rotation.size())
        return glm::mat4(1);
      return translation[animMap[x]] * rotation[animMap[x]];
    };

    std::vector<glm::mat4> result;
    result.resize(_model->bones.size());

    for (int i = 0; i < result.size(); i++) {
      glm::mat4 fwd = inverse[i];
      for (int chainIndex = 0; chainIndex < parentChain[i].size(); chainIndex++) {
        int p = parentChain[i][chainIndex];
        fwd = r(p) * fwd;
      }
      result[i] = fwd;
    }

    return result;
  }

}