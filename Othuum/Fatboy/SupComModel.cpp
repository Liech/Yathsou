#include "SupComModel.h"

#include "AhwassaGraphicsLib/Uniforms/Texture.h"
#include "AezeselFileIOLib/ImageIO.h"
#include "SCM.h"
#include "SCA.h"

#include "HaasScriptingLib/lib/json.hpp"
#include <filesystem>
#include <IyathuumCoreLib/lib/glm/gtx/quaternion.hpp>
#include <IyathuumCoreLib/lib/glm/gtx/euler_angles.hpp>
#include <fstream>
#include <iostream>

SupComModel::SupComModel(std::string foldername)
{
  _foldername = foldername;
  size_t lastSep = foldername.find_last_of('\\');
  std::string name = foldername.substr(lastSep+1);
  ////////auto albedoArray = YolonaOss::ImageIO::readImage(foldername + "\\" + name + "_Albedo.dds");
  ////////auto infoArray   = YolonaOss::ImageIO::readImage(foldername + "\\" + name + "_SpecTeam.dds");
  ////////auto normalArray = YolonaOss::ImageIO::readImage(foldername + "\\" + name + "_normalsTS.dds");
  //YolonaOss::ImageIO::writeImage("Albedo.png"  , *albedoArray);
  //YolonaOss::ImageIO::writeImage("SpecTeam.png", *teamArray  );
  //YolonaOss::ImageIO::writeImage("Normal.png"  , *normalArray);
  //auto albedoArrayLOD1 = YolonaOss::ImageIO::readImage(foldername + "\\" + name + "_lod1_Albedo.dds");
  //auto teamArrayLOD1   = YolonaOss::ImageIO::readImage(foldername + "\\" + name + "_lod1_normalsTS.dds");
  //auto normalArrayLOD1 = YolonaOss::ImageIO::readImage(foldername + "\\" + name + "_lod1_SpecTeam.dds");
  _albedo = std::make_shared<Ahwassa::Texture>("Albedo"  , 0);//////albedoArray.get());
  _info   = std::make_shared<Ahwassa::Texture>("TeamSpec", 0);//////infoArray  .get());
  _normal = std::make_shared<Ahwassa::Texture>("Normal"  , 0);//////normalArray.get());  
  //_albedoLOD1 = std::make_shared<YolonaOss::GL::Texture>("Albedo"  , albedoArray.get());
  //_teamLOD1   = std::make_shared<YolonaOss::GL::Texture>("TeamSpec", teamArray  .get());
  //_normalLOD1 = std::make_shared<YolonaOss::GL::Texture>("Normal"  , normalArray.get());
  SCM loader;
  _model = std::make_shared<SCM::data>(loader.load(foldername + "\\" + name + "_lod0.scm"));

  for (const auto& entry : std::filesystem::directory_iterator(foldername))
  {
    std::string animationPath = entry.path().string();
    if (animationPath.substr(animationPath.size()-4) == ".sca")
    {
      size_t      animSeperator = animationPath.find_last_of('\\');
      std::string animationName = animationPath.substr(animSeperator + 1/*\\*/ + name.size() + 2/*_A*/);
      animationName = animationName.substr(0, animationName.size() - 4);
      SCA animLoader;
      std::shared_ptr<SCA::data> anim = std::make_shared<SCA::data>(animLoader.load(animationPath));
      _animations[animationName] = anim;    
    }
  }

  //for (auto anim : _animations)
  //{
  //  std::ofstream stream;
  //  stream.open("walkAnim.json");
  //  nlohmann::json j = _animations["walk"]->toJson();
  //  stream << j.dump(4);
  //  stream.close();
  //
  //  int s0 = _animations["walk"]->animation[0].bones.size();
  //  for (auto an : _animations["walk"]->animation)
  //    if (an.bones.size() != s0) throw std::runtime_error("Wahh");
  //}
}

glm::mat4 SupComModel::toAnimation(const glm::mat4& input, int bone) const
{
  return glm::translate(input, -_model->bones[bone].position);
  //return input;// *glm::inverse(_model->bones[bone].relativeInverseMatrix)/**_model->bones[bone].relativeInverseMatrix*/;
}

glm::mat4 QuatToMat(glm::quat input)
{
  glm::vec3 euler = glm::eulerAngles(input) * 3.14159f / 180.f;

  glm::mat4 transformX = glm::eulerAngleX(euler.x);
  glm::mat4 transformY = glm::eulerAngleY(euler.y);
  glm::mat4 transformZ = glm::eulerAngleZ(euler.z);

  return transformX * transformY * transformZ; // or some other order
}

void SupComModel::animate(std::string animation, float time, std::vector<glm::mat4>& outVector)
{
  auto anim = _animations[animation];
  time = std::fmod(time, anim->duration);
  int no = (time / anim->duration) * anim->animation.size();
  //std::cout << no<<std::endl;
  auto frame = anim->animation[(int)(no)];
  
  for (int i = 0; i < frame.bones.size(); i++){
  //int i = 0; {
    auto bone = frame.bones[i];
    glm::mat4 boneMovement(1.0);
    //glm::mat4 rotated = QuatToMat(bone.rotation);
    //boneMovement = rotated*glm::translate(boneMovement,bone.position);
    outVector[i] = toAnimation(boneMovement,i);
  }

  //for (int i = 0; i < outVector.size(); i++){
  //  if (anim->boneLinks.size() <= i)
  //    return;
  //  assert(anim->boneLinks[i] < i);
  //  if (anim->boneLinks[i] != -1)
  //    outVector[i] = outVector[anim->boneLinks[i]] * outVector[i];
  //}
}
