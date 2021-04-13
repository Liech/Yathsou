#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>
#include "IyathuumCoreLib/lib/glm/vec3.hpp"
#include "IyathuumCoreLib/lib/glm/gtc/type_ptr.hpp"
#include "IyathuumCoreLib/lib/glm/glm.hpp"
#include "AezeselFileIOLib/lib/json.hpp"

//based on
//https://github.com/Oygron/SupCom_Import_Export_Blender/blob/master/supcom-importer.py

namespace Aezesel {
  //supreme commander model format
  class SCM
  {
  public:
    struct data;
    SCM::data load(std::string filename);
    static void save(std::string filename, const SCM::data&);

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

      nlohmann::json toJson();
      void fromJson(const nlohmann::json&);
    };

  private:
    int                      pad(int size);
    std::vector<std::string> split(std::string, char seperator = '\0');

    std::string              readString(const std::vector<unsigned char>&, size_t& position, size_t size);
    int                      readInt(const std::vector<unsigned char>&, size_t& position);
    unsigned short           readUShort(const std::vector<unsigned char>&, size_t& position);
    float                    readFloat(const std::vector<unsigned char>&, size_t& position);

    std::vector<std::string> readBoneNames(int offset);
    std::vector<bone>        readBones(int offset, int count, std::vector<std::string> boneNames);
    std::vector<vertex>      readVertices(int offset, int count);
    std::vector<tri>         readInidices(int offset, int count);
    std::vector<std::string> readInfo(int offset, int count);

    static void writeString(std::ofstream&, const std::string&);
    static void writeInt(std::ofstream&, const int&);
    static void writeUInt(std::ofstream&, const unsigned int&);
    static void writeUShort(std::ofstream&, const unsigned short&);
    static void writeFloat(std::ofstream&, const float&);

    static void writeBoneNames(std::ofstream&,const SCM::data&);
    static void writeBones    (std::ofstream&,const SCM::data&);
    static void writeVertices (std::ofstream&,const SCM::data&);
    static void writeInidices (std::ofstream&,const SCM::data&);
    static void writeInfo     (std::ofstream&,const SCM::data&);

    size_t      _fileposition = 0;
    std::vector<unsigned char> _buffer;
  };
}