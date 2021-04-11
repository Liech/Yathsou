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


        std::ofstream stream2;
        stream2.open(unitName + "_" + animationName + "_anim.json");
        nlohmann::json jd = anim->toJson();
        stream2 << jd.dump(4);
        stream2.close();
      }
    }


    std::ofstream stream;
    stream.open(unitName + "_model.json");
    nlohmann::json j = _model->toJson();
    stream << j.dump(4);
    stream.close();


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


  std::vector<glm::mat4> SupComModel::wargh(const std::string& name, float time) {
    std::vector<glm::mat4> inverse;
    std::vector<glm::mat4> forward;
    inverse.resize(_model->bones.size());
    forward.resize(_model->bones.size());
    for (int i = 0; i < inverse.size(); i++) {
      inverse[i] = _model->bones[i].relativeInverseMatrix;
      forward[i] = glm::inverse(_model->bones[i].relativeInverseMatrix);
    }

    std::vector<glm::mat4> localForward;
    for (int i = 0; i < _model->bones.size(); i++) {
      glm::mat4 local;
      int parentIndex = _model->bones[i].parentIndex;
      if (parentIndex != -1)
        local = forward[i] * inverse[parentIndex];
      else
        local = forward[i];

      localForward.push_back(local);
    }

    std::vector<std::vector<int>> parentChain;

    for (int i = 0; i < _model->bones.size(); i++) {
      std::vector<int> chain;
      chain.push_back(i);

      while (_model->bones[chain.back()].parentIndex != -1)
        chain.push_back(_model->bones[chain.back()].parentIndex);
      parentChain.push_back(chain);
    }

    auto& anim = _animations[name];
    int frameno = (int)((time / anim->duration) * (anim->animation.size() - 1)) + 1;
    Aezesel::SCA::frame frame = anim->animation[frameno];
    std::vector<glm::mat4> rotation;
    for (int i = 0; i < frame.bones.size(); i++)
    {
      glm::quat iden = glm::identity<glm::quat>();
      glm::quat rot = glm::normalize(frame.bones[i].rotation);
      glm::mat4 sub = Aezesel::SCA::QuatToMat(rot);
      rotation.push_back(sub);
    }
    std::map<std::string, int> preMap;
    std::map<int, int> animMap;
    for (int i = 0; i < anim->boneNames.size(); i++)
      preMap[anim->boneNames[i]] = i;
    for(int i =0;i < _model->boneNames.size();i++)
    {
      if (preMap.count(_model->bones[i].name) != 0)
        animMap[i] = preMap[_model->bones[i].name]+1;
      else
        animMap[i] = 0;
    }

    auto r = [&](int x) { 
      if (rotation.size() <= x)
        return glm::mat4(1);
      if (animMap[x] >= rotation.size())
        return glm::mat4(1);
      return rotation[animMap[x]]; 
    };

    std::vector<glm::mat4> result;
    result.resize(_model->bones.size());

    for (int i = 0; i < result.size(); i++) {
      glm::mat4 fwd = inverse[i];
      for (int chainIndex = 0; chainIndex < parentChain[i].size(); chainIndex++) {
        int p = parentChain[i][chainIndex];
        fwd = localForward[p] * r(p) * fwd;
      }
      result[i] = fwd;
    }

    //result[0]  =  localForward[0 ] *r(0)* inverse[0];
    //result[1]  =  localForward[0 ] *r(0)*  localForward[1 ] *r(1) * inverse[1];
    //result[2]  =  localForward[0 ] *r(0)*  localForward[2 ] *r(2) * inverse[2];
    //result[3]  =  localForward[0 ] *r(0)*  localForward[3 ] *r(3) * inverse[3];
    //result[4]  =  localForward[0 ] *r(0)*  localForward[2 ] *r(2) * localForward[4] *r(4)* inverse[4];
    //result[5]  =  localForward[0 ] *r(0)*  localForward[2 ] *r(2) * localForward[4] *r(4)* localForward[5] *r(5)* inverse[5];
    //result[6]  =  localForward[0 ] *r(0)*  localForward[2 ] *r(2) * localForward[4] *r(4)* localForward[5] *r(5)* localForward[6] * r(6)* inverse[6];
    //result[7]  =  localForward[0 ] *r(0)*  localForward[7 ] *r(7) * inverse[7];
    //result[8]  =  localForward[0 ] *r(0)*  localForward[8 ] *r(8) * inverse[8];
    //result[9]  =  localForward[0 ] *r(0)*  localForward[9 ] *r(9) * inverse[9];
    //result[10] =  localForward[0 ] *r(0)*  localForward[10] *r(10)* inverse[10];
    //result[11] =  localForward[0 ] *r(0)*  localForward[11] *r(11)* inverse[11];
    //result[12] =  localForward[0 ] *r(0)*  localForward[12] *r(12)* inverse[12];
    return result;
  }

  std::vector<glm::mat4> SupComModel::getAnimation(const std::string& name, float time) {

    std::vector<glm::mat4> result;
    auto& anim = _animations[name];
    result.resize(_model->bones.size());
    for (int i = 0; i < result.size(); i++)
      result[i] = glm::mat4(1.0f);

    std::vector<std::string> modelBonesp;
    std::map<std::string, int> modelBones;
    for (int i = 0; i < _model->bones.size(); i++) {
      modelBones[_model->bones[i].name] = i;
      modelBonesp.push_back(std::to_string(i)+ "__" + _model->bones[i].name + "__" + std::to_string(_model->bones[i].parentIndex));
    }
    std::map<std::string, int> animBones;
    for (int i = 0; i < anim->boneNames.size(); i++)
      animBones[anim->boneNames[i]] = i;

    auto anim2model = [&](int animationBone) {
      if (animationBone == -1)
        return -1;
      auto animBoneName = anim->boneNames[animationBone];
      if (modelBones.count(animBoneName) == 0)
        return 0;
      else
        return modelBones[animBoneName];
    };

    auto model2anim = [&](int modelBone) {
      if (modelBone == -1)
        return -1;
      auto modelBoneName = _model->boneNames[modelBone];      
      if (animBones.count(modelBoneName) == 0)
        return 0;
      else
        return animBones[modelBoneName];
    };

    std::vector<glm::mat4> inverse;
    std::vector<glm::mat4> forward;
    inverse.resize(anim->boneNames.size());
    forward.resize(anim->boneNames.size());
    for (int i = 0; i < inverse.size(); i++) {
      inverse[i] = _model->bones[anim2model(i)].relativeInverseMatrix;
      forward[i] = glm::inverse(_model->bones[anim2model(i)].relativeInverseMatrix);
    }

    std::vector<std::vector<int>> boneChain;

    for (int i = 0; i < anim->boneNames.size(); i++) {
      std::vector<int> chain;
      chain.push_back(i);
      
      while (_model->bones[anim2model(chain.back())].parentIndex != -1)
        chain.push_back(model2anim(_model->bones[anim2model(chain.back())].parentIndex));
      boneChain.push_back(chain);
    }

    int frameno = (int)((time / anim->duration) * (anim->animation.size()-1)) + 1;
    Aezesel::SCA::frame frame = anim->animation[frameno];

    std::vector<glm::mat4> rotation;
    for (int i = 0; i < frame.bones.size(); i++)
    {
      glm::quat iden = glm::identity<glm::quat>();
      glm::quat rot = glm::normalize(frame.bones[i].rotation);
      glm::mat4 sub = Aezesel::SCA::QuatToMat(rot);
      rotation.push_back(sub);
    }
    rotation.push_back(glm::mat4(1));

    std::vector<glm::mat4> translation;
    for (int i = 0; i < frame.bones.size(); i++)
    {
      glm::mat4 sub = glm::mat4(1.0);
      sub = glm::translate(sub, frame.bones[i].position);
      translation.push_back(sub);
    }

    std::vector<glm::mat4> localForward;
    for (int i = 0; i < frame.bones.size(); i++) {
      glm::mat4 local;
      int parentIndex = model2anim(_model->bones[anim2model(i)].parentIndex);
      if (parentIndex != -1)
        local = forward[i] * inverse[parentIndex];
      else
        local = forward[i];

      localForward.push_back(local);
    }


    for (int i = 0; i < inverse.size(); i++) {
      glm::mat4 fwd = glm::mat4(1.0);
      for(int chainIndex = 0; chainIndex < boneChain[i].size(); chainIndex++){
        int p = boneChain[i][chainIndex];
        fwd = localForward[p]* rotation[p + 1] * fwd;        
      }
      result[anim2model(i)] = fwd*inverse[i];
    }

    std::map<std::string, glm::mat4> rrresssuuult;
    for (int i = 0; i < result.size(); i++) {
      rrresssuuult[_model->boneNames[i]] = result[i];
    }


    std::map<int, int> model2animmap;
    for (int i = 0; i < _model->boneNames.size(); i++)
      model2animmap[i] = model2anim(i);


    return wargh(name,time);


    return result;
  }

}