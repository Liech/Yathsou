#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include "glm/vec3.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/glm.hpp"
#include <nlohmann/json.hpp>
#include "AezeselFileIOLib/IO.h"

//supreme commander animation format
namespace Aezesel {
  class SCA : public IO
  {
  public:
    struct data;
    SCA::data load(std::string filename);
    SCA::data load(const std::vector<unsigned char>&);
    static void save(std::string filename, const SCA::data&); // not tested


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
    static glm::mat4 QuatToMat(glm::quat q);

  private:
    SCA::data internalLoad();

    std::vector<std::string> split(std::string, char seperator = '\0');

    std::vector<int>         readLinks(int numberOfBones);
    std::vector<std::string> readBoneNames(int offset, int length);
    glm::vec3                readPosition();
    glm::quat                readRotation();
    std::vector<frame>       readAnimation(int offset, int numberOfFrames, std::vector<std::string> boneNames);

    static void         writeLinks(std::ofstream&, const SCA::data&);
    static void         writeBoneNames(std::ofstream&, const SCA::data&);
    static void         writePosition(std::ofstream&, const SCA::data&);
    static void         writeRotation(std::ofstream&, const SCA::data&);
    static int          writeAnimation(std::ofstream&, const SCA::data&);

    size_t                     _fileposition;
    std::vector<unsigned char> _buffer;
  };
}