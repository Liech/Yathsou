#include "SupComModel.h"

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
}