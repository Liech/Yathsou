#pragma once

#include <string>
#include <vector>
#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>
#include "IyathuumCoreLib/lib/glm/vec3.hpp"
#include "IyathuumCoreLib/lib/glm/gtc/type_ptr.hpp"
#include "IyathuumCoreLib/lib/glm/glm.hpp"
#include "HaasScriptingLib/lib/json.hpp"

#include "VishalaNetworkLib/lib/json.hpp"

//supreme commander animation format
namespace Aezesel {
  class SCA
  {
  public:
    struct data;
    SCA::data load(std::string filename);
    static glm::mat4 QuatToMat(glm::quat q);

    struct bone
    {
      glm::vec3   position;
      glm::quat   rotation;
    };
    struct frame
    {
      float             keytime;//ignored at least by blender import/export
      unsigned int      keyflags;//ignored at least by blender import/export
      std::vector<bone> bones;//same throughout all frames
      std::string flag2str();
    };
    struct data
    {
      float                    duration;
      std::vector<std::string> boneNames;
      std::vector<int>         boneLinks;
      glm::vec3                position; //can contain weird values. ignored by blender
      glm::quat                rotation; //can contain weird values. ignored by blender
      std::vector<frame>       animation;

      nlohmann::json toJson();
      void           fromJson(nlohmann::json);
    };

  private:
    std::vector<std::string> split(std::string, char seperator = '\0');

    std::string  readString(const std::vector<unsigned char>&, size_t& position, size_t size);
    int          readInt(const std::vector<unsigned char>&, size_t& position);
    unsigned int readUInt(const std::vector<unsigned char>&, size_t& position);
    float        readFloat(const std::vector<unsigned char>&, size_t& position);

    std::vector<int>         readLinks(int numberOfBones);
    std::vector<std::string> readBoneNames(int offset, int length);
    glm::vec3                readPosition();
    glm::quat                readRotation();
    std::vector<frame>       readAnimation(int offset, int numberOfFrames, std::vector<std::string> boneNames);

    size_t                     _fileposition;
    std::vector<unsigned char> _buffer;
  };
}