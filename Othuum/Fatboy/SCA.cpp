#include "SCA.h"
#include <fstream>
#include <iostream>
#include <sstream>

//based on
//https://github.com/Oygron/SupCom_Import_Export_Blender/blob/master/supcom-importer.py

SCA::data SCA::load(std::string filename)
{
  SCA::data result;
  std::ifstream input(filename, std::ios::binary);
  if (input.fail())
    throw std::runtime_error("Error opening " + filename);
  
  _buffer       = std::vector<unsigned char>(std::istreambuf_iterator<char>(input), {});
  _fileposition = 0;

  std::string magic  = readString(_buffer, _fileposition, 4);
  int version        = readInt   (_buffer, _fileposition   );
  int numberOfFrames = readInt   (_buffer, _fileposition   );
  result.duration    = readFloat (_buffer, _fileposition   );
  int numberOfBones  = readInt   (_buffer, _fileposition   );
  int namesOffset    = readInt   (_buffer, _fileposition   );
  int linksOffset    = readInt   (_buffer, _fileposition   );
  int animationOffset= readInt   (_buffer, _fileposition   );
  int frameSize      = readInt   (_buffer, _fileposition   );

  if (magic != "ANIM")
    throw std::runtime_error("File not sca");
  if (version != 5)
    throw std::runtime_error("Unsupported version");

  result.boneNames = readBoneNames(namesOffset, linksOffset-namesOffset);
  result.boneLinks = readLinks    (numberOfBones);
  result.position  = readPosition ();
  result.rotation  = readRotation ();
  result.animation = readAnimation(animationOffset,numberOfFrames, result.boneNames);
  return result;
}

std::vector<SCA::frame> SCA::readAnimation(int offset, int numberOfFrames, std::vector<std::string> boneNames)
{
  _fileposition = offset;
  std::vector<frame> result;
  for (int i = 0; i < numberOfFrames; i++)
  {
    frame subresult;
    subresult.keytime     = readFloat(_buffer, _fileposition);
    subresult.keyflags    = readInt  (_buffer, _fileposition);

    for (int i = 0; i < boneNames.size(); i++)
    {
      bone b;
      b.position[0] = readFloat(_buffer, _fileposition);
      b.position[1] = readFloat(_buffer, _fileposition);
      b.position[2] = readFloat(_buffer, _fileposition);
      b.rotation[0] = readFloat(_buffer, _fileposition);
      b.rotation[1] = readFloat(_buffer, _fileposition);
      b.rotation[2] = readFloat(_buffer, _fileposition);
      b.rotation[3] = readFloat(_buffer, _fileposition);
      b.name = boneNames[i];

      subresult.bones.push_back(b);
    }

    result.push_back(subresult);
  }
  return result;
}

glm::vec3 SCA::readPosition()
{
  glm::vec3 result;
  result[0] = readInt(_buffer, _fileposition);
  result[1] = readInt(_buffer, _fileposition);
  result[2] = readInt(_buffer, _fileposition);
  return result;
}

glm::quat SCA::readRotation()
{
  glm::quat result;
  result[0] = readInt(_buffer, _fileposition);
  result[1] = readInt(_buffer, _fileposition);
  result[2] = readInt(_buffer, _fileposition);
  result[3] = readInt(_buffer, _fileposition);
  return result;
}

std::vector<int> SCA::readLinks(int numberOfBones)
{
  std::vector<int> result;
  for (int i = 0; i < numberOfBones; i++)
  {
    result.push_back(readInt(_buffer, _fileposition));
  }
  return result;
}

std::vector<std::string> SCA::readBoneNames(int nameoffset, int length)
{
  std::vector<std::string> result;
  _fileposition = nameoffset;
  std::string boneNames = readString(_buffer, _fileposition, length);
  result = split(boneNames);
  result.erase(result.begin() + result.size() - 1);
  return result;
}

float SCA::readFloat(const std::vector<unsigned char>& data, size_t& position)
{
  int  a = readInt(data, position);
  int* b = &a;
  float* c = (float*)b;
  return *c;
}

int SCA::readInt(const std::vector<unsigned char>& data, size_t& position)
{
  unsigned char bytes[] = { data[position],data[position + 1],data[position + 2],data[position + 3] };
  int* pInt = (int*)bytes;
  int result = *pInt;
  position += 4;
  return result;
}

std::string SCA::readString(const std::vector<unsigned char>& data, size_t& position, size_t size)
{
  char* d = (char*)data.data() + position;
  position += size;
  return std::string(d, size);
}

std::vector<std::string> SCA::split(std::string input, char seperator)
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