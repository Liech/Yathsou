#include "SupComModel.h"

#include "YolonaOss/OpenGL/Texture.h"
#include "YolonaOss/Util/ImageIO.h"
#include "SCM.h"
#include "SCA.h"

#include <filesystem>


SupComModel::SupComModel(std::string foldername)
{
  _foldername = foldername;
  size_t lastSep = foldername.find_last_of('\\');
  std::string name = foldername.substr(lastSep+1);
  auto albedoArray = YolonaOss::ImageIO::readImage(foldername + "\\" + name + "_Albedo.dds");
  auto teamArray = YolonaOss::ImageIO::readImage(foldername + "\\" + name + "_normalsTS.dds");
  auto normalArray = YolonaOss::ImageIO::readImage(foldername + "\\" + name + "_SpecTeam.dds");
  //auto albedoArrayLOD1 = YolonaOss::ImageIO::readImage(foldername + "\\" + name + "_lod1_Albedo.dds");
  //auto teamArrayLOD1   = YolonaOss::ImageIO::readImage(foldername + "\\" + name + "_lod1_normalsTS.dds");
  //auto normalArrayLOD1 = YolonaOss::ImageIO::readImage(foldername + "\\" + name + "_lod1_SpecTeam.dds");
  _albedo = std::make_shared<YolonaOss::GL::Texture>("Albedo"  , albedoArray.get());
  _team   = std::make_shared<YolonaOss::GL::Texture>("TeamSpec", teamArray  .get());
  _normal = std::make_shared<YolonaOss::GL::Texture>("Normal"  , normalArray.get());
  //_albedoLOD1 = std::make_shared<YolonaOss::GL::Texture>("Albedo"  , albedoArray.get());
  //_teamLOD1   = std::make_shared<YolonaOss::GL::Texture>("TeamSpec", teamArray  .get());
  //_normalLOD1 = std::make_shared<YolonaOss::GL::Texture>("Normal"  , normalArray.get());
  SCM loader;
  _model = std::make_shared<SCM::data>(loader.load(foldername + "\\" + name + "_lod0.scm"));

  for (const auto& entry : std::filesystem::directory_iterator(foldername))
  {
    std::string animationPath = entry.path().string();
    if (animationPath.ends_with(".sca"))
    {
      size_t      animSeperator = animationPath.find_last_of('\\');
      std::string animationName = animationPath.substr(animSeperator + 1/*\\*/ + name.size() + 2/*_A*/);
      animationName = animationName.substr(0, animationName.size() - 4);
      SCA animLoader;      
      std::shared_ptr<SCA::data> anim = std::make_shared<SCA::data>(animLoader.load(animationPath));
      _animations[animationName] = anim;    
    }
  }
}
