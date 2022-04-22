#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <IyathuumCoreLib/BaseTypes/glmAABB.h>
#include <nlohmann/json.hpp>
#include "AezeselFileIOLib/IO.h"

//based on
//https://github.com/Oygron/SupCom_Import_Export_Blender/blob/master/supcom-importer.py

namespace Aezesel {
  //supreme commander model format
  class SCM: public IO
  {
  public:
    struct data;
    SCM::data load(std::string filename);
    SCM::data load(const std::vector<unsigned char>& buffer);
    static void save(std::string filename, const SCM::data&);//not tested

    struct bone {
      std::string   name;
      glm::mat4     relativeInverseMatrix;
      glm::vec3     position;
      glm::quat     rotation;
      int           parentIndex;
    };

    struct vertex {
      glm::vec3     position;
      glm::vec3     tangent;
      glm::vec3     normal;
      glm::vec3     binormal;
      glm::vec2     uv1;
      glm::vec2     uv2;
      unsigned char boneIndex[4];
    };

    struct tri
    {
      unsigned short a;
      unsigned short b;
      unsigned short c;
    };

    struct data
    {
      std::vector<std::string>  boneNames;
      std::vector<bone>         bones;
      std::vector<vertex>       vertecies;
      std::vector<tri>          indices;
      std::vector<std::string>  info;
      Iyathuum::glmAABB<3>      aabb;

      nlohmann::json toJson();
      void fromJson(const nlohmann::json&);
    };

  private:
    SCM::data                loadInternal();
    int                      pad(int size);
    std::vector<std::string> split(std::string, char seperator = '\0');

    std::vector<std::string> readBoneNames(int offset);
    std::vector<bone>        readBones(int offset, int count, std::vector<std::string> boneNames);
    std::vector<vertex>      readVertices(int offset, int count, Iyathuum::glmAABB<3>& aabb);
    std::vector<tri>         readInidices(int offset, int count);
    std::vector<std::string> readInfo(int offset, int count);


    static void writeBoneNames(std::ofstream&,const SCM::data&);
    static void writeBones    (std::ofstream&,const SCM::data&);
    static void writeVertices (std::ofstream&,const SCM::data&);
    static void writeInidices (std::ofstream&,const SCM::data&);
    static void writeInfo     (std::ofstream&,const SCM::data&);

    size_t      _fileposition = 0;
    std::vector<unsigned char> _buffer;    
  };
}