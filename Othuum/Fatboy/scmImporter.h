#pragma once

#include <string>
#include <vector>
#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>
#include "IyathuumCoreLib/lib/glm/vec3.hpp"
#include "IyathuumCoreLib/lib/glm/gtc/type_ptr.hpp"
#include "IyathuumCoreLib/lib/glm/glm.hpp"

//based on
//https://github.com/Oygron/SupCom_Import_Export_Blender/blob/master/supcom-importer.py

class scmImporter
{
public:
  void work();
  
private:
  int pad(int size);
  std::vector<std::string> split(std::string);
  std::string readString(const std::vector<unsigned char>&, size_t& position, size_t size);
  int         readInt(const std::vector<unsigned char>&, size_t& position);
  float       readFloat(const std::vector<unsigned char>&, size_t& position);

  int _version         = 0;
  int _bonecount       = 0;
  int _vertoffset      = 0;
  int _extravertoffset = 0;
  int _vertcount       = 0;
  int _indexoffset     = 0;
  int _indexcount      = 0;
  int _tricount        = 0;
  int _infooffset      = 0;
  int _infocount       = 0;
  struct bone {
    std::string   name;
    glm::mat4     relativeInverseMatrix;
    glm::vec3     position;
    glm::quat     rotation;
    int           parentIndex;
  };
  struct vertex {
    glm::vec3     position    ;
    glm::vec3     tangent     ;
    glm::vec3     normal      ;
    glm::vec3     binormal    ;
    glm::vec2     uv1         ;
    glm::vec2     uv2         ;
    unsigned char boneIndex[4];

  };
  
  std::vector<std::string> readBoneNames(int offset);
  std::vector<bone>        readBones(int offset,int count,std::vector<std::string> boneNames);
  std::vector<vertex>      readVertices(int offset,int count);

  std::string folder = "E:\\scmunpacked\\units\\UES0103";
  std::string lod1   = "UES0103_lod1.scm";
  std::string lod0   = "UES0103_LOD0.scm";

  size_t      _fileposition = 0;
  std::vector<unsigned char> _buffer;
};