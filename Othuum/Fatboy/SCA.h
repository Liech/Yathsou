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
  struct data;
  SCA::data load(std::string filename);

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
  struct data
  {
    float                    duration ;
    std::vector<std::string> boneNames;
    std::vector<int>         boneLinks;
    glm::vec3                position ;
    glm::quat                rotation ;
    std::vector<frame>       animation;
  };

private:
  std::vector<std::string> split(std::string, char seperator = '\0');

  std::string readString(const std::vector<unsigned char>&, size_t& position, size_t size);
  int         readInt   (const std::vector<unsigned char>&, size_t& position);
  float       readFloat (const std::vector<unsigned char>&, size_t& position);

  std::vector<int>         readLinks    (int numberOfBones);
  std::vector<std::string> readBoneNames(int offset, int length);
  glm::vec3                readPosition ();
  glm::quat                readRotation ();
  std::vector<frame>       readAnimation(int offset, int numberOfFrames, std::vector<std::string> boneNames);

  size_t                     _fileposition;
  std::vector<unsigned char> _buffer      ;
};