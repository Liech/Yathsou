#include "scmImporter.h"

#include <fstream>
#include <iostream>
#include <sstream>

void scmImporter::work()
{
  std::string file = folder + "\\" + lod1;

  std::ifstream input(file, std::ios::binary);
  if (input.fail())
    throw std::runtime_error("Error opening " + file);
  _buffer = std::vector<unsigned char>(std::istreambuf_iterator<char>(input), {});

  /*
  SimpleOperator
  scm_bone
  scm_vertex
  scm_mesh
  sca_bone
  sca_frame
  sca_anim
  pad

  read_scm
  iterate_bones
  get_mesh_bones
  read_anim
  check_bone
  read_end_anim
  IMPORT_OT_scm
  IMPORT_OT_sca
  menu_func
  register
  unregister
  */
  std::string marker         = readString(_buffer, _fileposition,4);
  _version        = readInt   (_buffer, _fileposition);
  _boneoffset     = readInt   (_buffer, _fileposition);
  _bonecount      = readInt   (_buffer, _fileposition);
  _vertoffset     = readInt   (_buffer, _fileposition);
  _extravertoffset= readInt   (_buffer, _fileposition);
  _vertcount      = readInt   (_buffer, _fileposition);
  _indexoffset    = readInt   (_buffer, _fileposition);
  _indexcount     = readInt   (_buffer, _fileposition);
  _tricount       = readInt   (_buffer, _fileposition);
  _infooffset     = readInt   (_buffer, _fileposition);
  _infocount      = readInt   (_buffer, _fileposition);
  _totalbonecount = readInt   (_buffer, _fileposition);

  if (marker != "MODL")
    throw std::runtime_error("File not scm");
  if (_version != 5)
    throw std::runtime_error("Unsupported version");

  readBoneNames();

  throw std::runtime_error("Unfinished");
  //supcom importer
  //for b in range(0, totalbonecount):


}

void scmImporter::readBoneNames()
{
  _fileposition += pad(_fileposition);
  int boneDescriptionLength = (_boneoffset - 4) - _fileposition;
  std::string boneNames = readString(_buffer, _fileposition, boneDescriptionLength);
  _boneNames = split(boneNames);
  _boneNames.erase(_boneNames.begin() + _boneNames.size() - 1);
}

int scmImporter::readInt(const std::vector<unsigned char>& data, size_t& position)
{
  unsigned char bytes[] = { data[position],data[position + 1],data[position + 2],data[position + 3] };
  int* pInt = (int*)bytes;
  int result = *pInt;
  position += 4;
  return result;
}

std::string scmImporter::readString(const std::vector<unsigned char>& data, size_t& position, size_t size)
{
  char* d = (char*)data.data() + position;
  position += size;
  return std::string(d, size);
}

std::vector<std::string> scmImporter::split(std::string input)
{
  std::vector<std::string> seglist;
  std::string segment;
  std::stringstream stream(input);

  while (std::getline(stream, segment, '\0'))
  {
    seglist.push_back(segment);
  }
  return seglist;
}

int scmImporter::pad(int size)
{
  int val = 32 - (size % 32);
  if (val > 31)
    return 0;
  return val;
}