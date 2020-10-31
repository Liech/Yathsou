#pragma once

#include <string>
#include <vector>

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

  int _version         = 0;
  int _boneoffset      = 0;
  int _bonecount       = 0;
  int _vertoffset      = 0;
  int _extravertoffset = 0;
  int _vertcount       = 0;
  int _indexoffset     = 0;
  int _indexcount      = 0;
  int _tricount        = 0;
  int _infooffset      = 0;
  int _infocount       = 0;
  int _totalbonecount  = 0;
  std::vector<std::string> _boneNames;

  void readBoneNames();

  std::string folder = "E:\\scmunpacked\\units\\UES0103";
  std::string lod1   = "UES0103_lod1.scm";
  std::string lod0   = "UES0103_LOD0.scm";

  size_t      _fileposition = 0;
  std::vector<unsigned char> _buffer;
};