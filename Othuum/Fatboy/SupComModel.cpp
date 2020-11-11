#include "SupComModel.h"

#include "YolonaOss/OpenGL/Texture.h"
#include "YolonaOss/Util/ImageIO.h"
#include "SCM.h"
#include "SCA.h"

#include <filesystem>
#include <IyathuumCoreLib/lib/glm/gtx/quaternion.hpp>

SupComModel::SupComModel(std::string foldername)
{
  _foldername = foldername;
  size_t lastSep = foldername.find_last_of('\\');
  std::string name = foldername.substr(lastSep+1);
  auto albedoArray = YolonaOss::ImageIO::readImage(foldername + "\\" + name + "_Albedo.dds");
  auto infoArray   = YolonaOss::ImageIO::readImage(foldername + "\\" + name + "_SpecTeam.dds");
  auto normalArray = YolonaOss::ImageIO::readImage(foldername + "\\" + name + "_normalsTS.dds");
  //YolonaOss::ImageIO::writeImage("Albedo.png"  , *albedoArray);
  //YolonaOss::ImageIO::writeImage("SpecTeam.png", *teamArray  );
  //YolonaOss::ImageIO::writeImage("Normal.png"  , *normalArray);
  //auto albedoArrayLOD1 = YolonaOss::ImageIO::readImage(foldername + "\\" + name + "_lod1_Albedo.dds");
  //auto teamArrayLOD1   = YolonaOss::ImageIO::readImage(foldername + "\\" + name + "_lod1_normalsTS.dds");
  //auto normalArrayLOD1 = YolonaOss::ImageIO::readImage(foldername + "\\" + name + "_lod1_SpecTeam.dds");
  _albedo = std::make_shared<YolonaOss::GL::Texture>("Albedo"  , albedoArray.get());
  _info   = std::make_shared<YolonaOss::GL::Texture>("TeamSpec", infoArray  .get());
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

glm::mat4 SupComModel::toAnimation(const glm::mat4& input, int bone) const
{
  return glm::inverse(_model->bones[bone].relativeInverseMatrix)*input/**_model->bones[bone].relativeInverseMatrix*/  ;
}

void SupComModel::animate(std::string animation, float time, std::vector<glm::mat4>& outVector)
{
  auto anim = _animations[animation];
  time = std::fmod(time, anim->duration);
  auto frame = anim->animation[(int)((time / anim->duration) * anim->animation.size())];
  
  for (int i = 0; i < frame.bones.size(); i++){
    auto bone = frame.bones[i];
    glm::mat4 boneMovement(1.0);
    boneMovement = glm::translate(glm::toMat4(bone.rotation),bone.position);
    outVector[i] = toAnimation(boneMovement,i);
  }
}
