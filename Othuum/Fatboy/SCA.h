#pragma once

#include <string>
#include <vector>
#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>
#include "IyathuumCoreLib/lib/glm/vec3.hpp"
#include "IyathuumCoreLib/lib/glm/gtc/type_ptr.hpp"
#include "IyathuumCoreLib/lib/glm/glm.hpp"

//supreme commander animation format
class SCA
{
public:
  void work();


  struct bone
  {
    glm::vec3   position;
    glm::quat   rotation;
    std::string name    ;
  };
  struct frame
  {
    float             keytime ;
    int               keyflags;
    std::vector<bone> bones   ;
  };

private:
  std::vector<std::string> split(std::string, char seperator = '\0');
  std::string readString(const std::vector<unsigned char>&, size_t& position, size_t size);
  int         readInt   (const std::vector<unsigned char>&, size_t& position);
  float       readFloat (const std::vector<unsigned char>&, size_t& position);

  std::vector<int>         readLinks(int numberOfBones);
  std::vector<std::string> readBoneNames(int offset, int length);
  glm::vec3                readPosition();
  glm::quat                readRotation();
  std::vector<frame>       readAnimation(int offset, int numberOfFrames, std::vector<std::string> boneNames);

  std::string folder = "E:\\scmunpacked\\units\\UES0103";
  std::string a1    = "UES0103_A001.sca";
  std::string a2    = "UES0103_A002.sca";
  std::string death1 = "UES0103_ADeath01.sca";
  std::string death2 = "UES0103_ADeath02.sca";

  size_t                     _fileposition = 0;
  std::vector<unsigned char> _buffer;
};