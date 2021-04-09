#pragma once

#include <string>
#include <memory>
#include <map>
#include "AezeselFileIOLib/SCM.h"
#include "AezeselFileIOLib/SCA.h"
namespace Ahwassa
{
  class Texture;
}

struct SupComModel
{
  SupComModel(std::string foldername);

  std::string                                _foldername;
  std::shared_ptr<Ahwassa::Texture>          _albedo    ;
  std::shared_ptr<Ahwassa::Texture>          _info      ;
  std::shared_ptr<Ahwassa::Texture>          _normal    ;
  //std::shared_ptr<Ahwassa::Texture>        _albedoLOD1;
  //std::shared_ptr<Ahwassa::Texture>        _teamLOD1  ;
  //std::shared_ptr<Ahwassa::Texture>        _normalLOD1;
  std::shared_ptr<Aezesel::SCM::data>                       _model     ;
  std::map<std::string,std::shared_ptr<Aezesel::SCA::data>> _animations;


  glm::mat4 toAnimation(const glm::mat4&,int bone) const;
  void animate(std::string animation, float time, std::vector<glm::mat4>& outVector);
};