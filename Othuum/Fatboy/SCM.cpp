#include "SCM.h"

#include <fstream>
#include <iostream>
#include <sstream>

SCM::data SCM::load(std::string filename)
{
  SCM::data result;

  std::ifstream input(filename, std::ios::binary);
  if (input.fail())
    throw std::runtime_error("Error opening " + filename);
  
  _buffer       = std::vector<unsigned char>(std::istreambuf_iterator<char>(input), {});
  _fileposition = 0;
  
  std::string marker = readString(_buffer, _fileposition,4);
  int version        = readInt   (_buffer, _fileposition);
  int boneoffset     = readInt   (_buffer, _fileposition);
  int bonecount      = readInt   (_buffer, _fileposition);//unused
  int vertoffset     = readInt   (_buffer, _fileposition);
  int extravertoffset= readInt   (_buffer, _fileposition); //unused
  int vertcount      = readInt   (_buffer, _fileposition);
  int indexoffset    = readInt   (_buffer, _fileposition);
  int indexcount     = readInt   (_buffer, _fileposition);
  int tricount       = indexcount /3;
  int infooffset     = readInt   (_buffer, _fileposition);
  int infocount      = readInt   (_buffer, _fileposition);
  int totalbonecount = readInt   (_buffer, _fileposition);

  if (marker != "MODL")
    throw std::runtime_error("File not scm");
  if (version != 5)
    throw std::runtime_error("Unsupported version");

  result.boneNames = readBoneNames(boneoffset);
  result.bones     = readBones    (boneoffset, totalbonecount,result.boneNames);
  result.vertecies = readVertices (vertoffset, vertcount);
  result.indices   = readInidices (indexoffset,tricount);
  result.info      = readInfo     (infooffset, infocount);

  return result;
}

std::vector<std::string> SCM::readInfo(int offset, int count)
{
  _fileposition = offset;
  std::string rest = readString(_buffer, _fileposition, _buffer.size() - offset);
  return split(rest);
}

std::vector<SCM::tri> SCM::readInidices(int offset, int count)
{
  std::vector<SCM::tri> result;
  _fileposition = offset;
  for (int i = 0; i < count/3; i++)
  {
    tri subresult;
    subresult.a = readInt(_buffer, _fileposition);
    subresult.b = readInt(_buffer, _fileposition);
    subresult.c = readInt(_buffer, _fileposition);
    result.push_back(subresult);
  }
  return result;
}

std::vector<SCM::vertex> SCM::readVertices(int vertoffset, int vertcount)
{
  std::vector<vertex> result;
  _fileposition = vertoffset;
  
  for (int i = 0; i < vertcount; i++)
  {
    vertex subresult;
    subresult.position[0]  = readFloat(_buffer, _fileposition);
    subresult.position[1]  = readFloat(_buffer, _fileposition);
    subresult.position[2]  = readFloat(_buffer, _fileposition);

    subresult.tangent [0]  = readFloat(_buffer, _fileposition);
    subresult.tangent [1]  = readFloat(_buffer, _fileposition);
    subresult.tangent [2]  = readFloat(_buffer, _fileposition);

    subresult.normal  [0]  = readFloat(_buffer, _fileposition);
    subresult.normal  [1]  = readFloat(_buffer, _fileposition);
    subresult.normal  [2]  = readFloat(_buffer, _fileposition);

    subresult.binormal[0]  = readFloat(_buffer, _fileposition);
    subresult.binormal[1]  = readFloat(_buffer, _fileposition);
    subresult.binormal[2]  = readFloat(_buffer, _fileposition);

    subresult.uv1     [0]  = readFloat(_buffer, _fileposition);
    subresult.uv1     [1]  = readFloat(_buffer, _fileposition);
    subresult.uv2     [0]  = readFloat(_buffer, _fileposition);
    subresult.uv2     [1]  = readFloat(_buffer, _fileposition);
    
    subresult.boneIndex[0] = _buffer[_fileposition+0];
    subresult.boneIndex[1] = _buffer[_fileposition+1];
    subresult.boneIndex[2] = _buffer[_fileposition+2];
    subresult.boneIndex[3] = _buffer[_fileposition+3];
    _fileposition += 4;

    result.push_back(subresult);
  }

  return result;
}

std::vector<SCM::bone> SCM::readBones(int boneoffset, int totalbonecount, std::vector<std::string> boneNames)
{
  std::vector<bone> result;
  _fileposition = boneoffset;
  for (int i = 0; i < totalbonecount; i++)
  {
    bone subResult;
    subResult.name = boneNames[i];
    float matrixInitializiation[16];
    for(int i = 0;i < 16;i++)
      matrixInitializiation[i] = readFloat(_buffer, _fileposition);
    subResult.relativeInverseMatrix = glm::make_mat4(matrixInitializiation);
    subResult.position[0] = readFloat(_buffer, _fileposition);
    subResult.position[1] = readFloat(_buffer, _fileposition);
    subResult.position[2] = readFloat(_buffer, _fileposition);
    subResult.rotation[0] = readFloat(_buffer, _fileposition);
    subResult.rotation[1] = readFloat(_buffer, _fileposition);
    subResult.rotation[2] = readFloat(_buffer, _fileposition);
    subResult.rotation[3] = readFloat(_buffer, _fileposition);
    int emptyDummy1 = readInt(_buffer, _fileposition);
    subResult.parentIndex = readInt  (_buffer, _fileposition);
    int emptyDummy2 = readInt(_buffer, _fileposition);
    int emptyDummy3 = readInt(_buffer, _fileposition);

    result.push_back(subResult);
  }
  return result;
}

std::vector<std::string> SCM::readBoneNames(int boneoffset)
{
  std::vector<std::string> result;
  _fileposition += pad(_fileposition);
  int boneDescriptionLength = (boneoffset - 4) - _fileposition;
  std::string boneNames = readString(_buffer, _fileposition, boneDescriptionLength);
  result = split(boneNames);
  result.erase(result.begin() + result.size() - 1);
  return result;
}

float SCM::readFloat(const std::vector<unsigned char>& data, size_t& position)
{
  int  a = readInt(data, position);
  int* b = &a;
  float* c = (float*)b;
  return *c;
}

int SCM::readInt(const std::vector<unsigned char>& data, size_t& position)
{
  unsigned char bytes[] = { data[position],data[position + 1],data[position + 2],data[position + 3] };
  int* pInt = (int*)bytes;
  int result = *pInt;
  position += 4;
  return result;
}

std::string SCM::readString(const std::vector<unsigned char>& data, size_t& position, size_t size)
{
  char* d = (char*)data.data() + position;
  position += size;
  return std::string(d, size);
}

std::vector<std::string> SCM::split(std::string input, char seperator)
{
  std::vector<std::string> seglist;
  std::string segment;
  std::stringstream stream(input);

  while (std::getline(stream, segment, seperator))
  {
    seglist.push_back(segment);
  }
  return seglist;
}

int SCM::pad(int size)
{
  int val = 32 - (size % 32);
  if (val > 31)
    return 0;
  return val;
}