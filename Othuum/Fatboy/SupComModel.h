#pragma once

#include <string>
#include <memory>
#include <map>
#include "SCM.h"
#include "SCA.h"
namespace YolonaOss
{
  namespace GL
  {
    class Texture;
  }
}

struct SupComModel
{
  SupComModel(std::string foldername);

  std::string                                      _foldername;
  std::shared_ptr<YolonaOss::GL::Texture>          _albedo    ;
  std::shared_ptr<YolonaOss::GL::Texture>          _team      ;
  std::shared_ptr<YolonaOss::GL::Texture>          _normal    ;
  //std::shared_ptr<YolonaOss::GL::Texture>        _albedoLOD1;
  //std::shared_ptr<YolonaOss::GL::Texture>        _teamLOD1  ;
  //std::shared_ptr<YolonaOss::GL::Texture>        _normalLOD1;
  std::shared_ptr<SCM::data>                       _model     ;
  std::map<std::string,std::shared_ptr<SCA::data>> _animations;
};