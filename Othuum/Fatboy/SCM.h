#pragma once

#include <string>
#include <vector>
#include <map>
#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>
#include "IyathuumCoreLib/lib/glm/vec3.hpp"
#include "IyathuumCoreLib/lib/glm/gtc/type_ptr.hpp"
#include "IyathuumCoreLib/lib/glm/glm.hpp"

//based on
//https://github.com/Oygron/SupCom_Import_Export_Blender/blob/master/supcom-importer.py


//dds:https://github.com/septag/dds-ktx


//supreme commander model format
class SCM
{
public:
  void work();
  
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
    short a;
    short b;
    short c;
  };

private:
  int                      pad(int size);
  std::vector<std::string> split(std::string, char seperator = '\0');
  std::string              readString(const std::vector<unsigned char>&, size_t& position, size_t size);
  int                      readInt   (const std::vector<unsigned char>&, size_t& position);
  float                    readFloat (const std::vector<unsigned char>&, size_t& position);

  int _bonecount       = 0;//~unused
  int _extravertoffset = 0;//~unused
  int _indexcount      = 0;//~unused

  std::vector<std::string> readBoneNames(int offset);
  std::vector<bone>        readBones    (int offset,int count,std::vector<std::string> boneNames);
  std::vector<vertex>      readVertices (int offset,int count);
  std::vector<tri>         readInidices (int offset, int count);
  std::vector<std::string> readInfo     (int offset, int count);

  std::string folder = "E:\\scmunpacked\\units\\UES0103";
  std::string lod1   = "UES0103_lod1.scm";
  std::string lod0   = "UES0103_LOD0.scm";

  size_t      _fileposition = 0;
  std::vector<unsigned char> _buffer;
};