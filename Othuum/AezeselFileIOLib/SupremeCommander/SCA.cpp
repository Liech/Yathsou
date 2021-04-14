#include "SCA.h"
#include <iostream>
#include <sstream>

#include <IyathuumCoreLib/lib/glm/gtc/matrix_transform.hpp>
#include "IyathuumCoreLib/lib/glm/gtc/type_ptr.hpp"

//based on
//https://github.com/Oygron/SupCom_Import_Export_Blender/blob/master/supcom-importer.py

namespace Aezesel {
  SCA::data SCA::load(std::string filename)
  {
    std::ifstream input(filename, std::ios::binary);
    if (input.fail())
      throw std::runtime_error("Error opening " + filename);
    _buffer = std::vector<unsigned char>(std::istreambuf_iterator<char>(input), {});
    return internalLoad();
  }

  SCA::data SCA::load(const std::vector<unsigned char>& buffer) {
    _buffer = buffer;
    return internalLoad();
  }

  SCA::data SCA::internalLoad() {
    SCA::data result;
    _fileposition = 0;

    std::string magic = readString(_buffer, _fileposition, 4);
    int version = readInt(_buffer, _fileposition);
    int numberOfFrames = readInt(_buffer, _fileposition);
    result.duration = readFloat(_buffer, _fileposition);
    int numberOfBones = readInt(_buffer, _fileposition);
    int namesOffset = readInt(_buffer, _fileposition);
    int linksOffset = readInt(_buffer, _fileposition);
    int animationOffset = readInt(_buffer, _fileposition);
    int frameSize = readInt(_buffer, _fileposition);

    if (magic != "ANIM")
      throw std::runtime_error("File not sca");
    if (version != 5)
      throw std::runtime_error("Unsupported version");

    result.boneNames = readBoneNames(namesOffset, linksOffset - namesOffset);
    result.boneLinks = readLinks(numberOfBones);
    result.position = readPosition();
    result.rotation = readRotation();
    result.animation = readAnimation(animationOffset, numberOfFrames, result.boneNames);
    return result;
  }

  std::vector<SCA::frame> SCA::readAnimation(int offset, int numberOfFrames, std::vector<std::string> boneNames)
  {
    _fileposition = offset;
    std::vector<frame> result;
    for (int i = 0; i < numberOfFrames; i++)
    {
      frame subresult;
      subresult.keytime = readFloat(_buffer, _fileposition);
      subresult.keyflags = readUInt(_buffer, _fileposition);

      for (int j = 0; j < boneNames.size(); j++)
      {
        bone b;

        b.position[0] = readFloat(_buffer, _fileposition);
        b.position[1] = readFloat(_buffer, _fileposition);
        b.position[2] = readFloat(_buffer, _fileposition);
        b.rotation[3] = readFloat(_buffer, _fileposition);
        b.rotation[0] = readFloat(_buffer, _fileposition);
        b.rotation[1] = readFloat(_buffer, _fileposition);
        b.rotation[2] = readFloat(_buffer, _fileposition);

        subresult.bones.push_back(b);
      }

      result.push_back(subresult);
    }
    return result;
  }

  glm::vec3 SCA::readPosition()
  {
    glm::vec3 result;
    result[0] = readFloat(_buffer, _fileposition);
    result[1] = readFloat(_buffer, _fileposition);
    result[2] = readFloat(_buffer, _fileposition);
    return result;
  }

  glm::quat SCA::readRotation()
  {
    glm::quat result;
    result[0] = readFloat(_buffer, _fileposition);
    result[1] = readFloat(_buffer, _fileposition);
    result[2] = readFloat(_buffer, _fileposition);
    result[3] = readFloat(_buffer, _fileposition);
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

  unsigned int SCA::readUInt(const std::vector<unsigned char>& data, size_t& position)
  {
    unsigned char bytes[] = { data[position],data[position + 1],data[position + 2],data[position + 3] };
    unsigned int* pInt = (unsigned int*)bytes;
    unsigned int result = *pInt;
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

  void SCA::data::fromJson(nlohmann::json input)
  {
    duration = input["Duration"];
    boneNames.clear();
    for (auto name : input["BoneNames"]) boneNames.push_back(name);
    for (auto name : input["BoneLinks"]) boneLinks.push_back(name);
    position = glm::vec3(input["Position"][0], input["Position"][1], input["Position"][2]);
    rotation = glm::quat(input["Rotation"][0], input["Rotation"][1], input["Rotation"][2], input["Rotation"][3]);
    for (auto anim : input["Animation"])
    {
      frame sub;
      sub.keytime = anim["Keytime"];
      sub.keyflags = anim["Keyflags"];
      for (auto jbone : anim["Bone"]) {
        bone b;
        b.position = glm::vec3(jbone["Position"][0], jbone["Position"][1], jbone["Position"][2]);
        b.rotation = glm::quat(jbone["Rotation"][0], jbone["Rotation"][1], jbone["Rotation"][2], jbone["Rotation"][3]);
        sub.bones.push_back(b);
      }
      animation.push_back(sub);
    }
  }
  
  nlohmann::json SCA::data::toJson()
  {
    nlohmann::json result;
    result["Duration"] = duration;
    result["BoneNames"] = boneNames;
    result["BoneLinks"] = boneLinks;
    result["Position"] = std::vector<float>{ position[0],position[1],position[2] };
    result["Rotation"] = std::vector<float>{ rotation[0],rotation[1],rotation[2],rotation[3] };
    std::vector<nlohmann::json> anim;
    for (auto a : animation)
    {
      nlohmann::json subresult;
      subresult["Keytime"] = a.keytime;
      subresult["Keyflags"] = a.keyflags;
      std::vector<nlohmann::json> bones;
      for (auto bone : a.bones) {
        nlohmann::json jbone;
        jbone["Position"] = std::vector<float>{ bone.position[0],bone.position[1],bone.position[2] };
        jbone["Rotation"] = std::vector<float>{ bone.rotation[0],bone.rotation[1],bone.rotation[2],bone.rotation[3] };
        bones.push_back(jbone);
      }
      subresult["Bone"] = bones;
      anim.push_back(subresult);
    }
    result["Animation"] = anim;
    return result;
  }


  glm::mat4 SCA::QuatToMat(glm::quat q)
  {
    return glm::mat4_cast(q);
  }

  std::string SCA::frame::flag2str() {
    std::string result = "";
    for(int i = 0;i < 32;i++)
      result += ((keyflags >> i) % 2) ? "1" : "0";
    return result;
  }


  void SCA::save(std::string filename, const SCA::data& data) {
    std::ofstream outfile(filename, std::ofstream::binary);

    writeString(outfile, "ANIM");
    writeInt   (outfile, 5);
    writeInt   (outfile, data.animation.size());
    writeFloat (outfile, data.duration);
    writeInt   (outfile, data.boneNames.size());
    
    size_t offsetPosition = outfile.tellp();

    //come back later to this
    writeInt(outfile, 0); //names offset
    writeInt(outfile, 0); //links offset
    writeInt(outfile, 0); //animation offset
    writeInt(outfile, 0); //framesize

    size_t namesOffset = outfile.tellp();
    writeBoneNames(outfile, data);
    size_t linksOffset = outfile.tellp();
    writeLinks(outfile, data);
    writePosition(outfile,data);
    writeRotation(outfile,data);
    size_t animationOffset = outfile.tellp();
    int frameSize = writeAnimation(outfile, data);

    //now everything is known to go back
    outfile.seekp(offsetPosition);
    writeInt(outfile, namesOffset);
    writeInt(outfile, linksOffset);
    writeInt(outfile, animationOffset);
    writeInt(outfile, frameSize);
  }

  void SCA::writeLinks(std::ofstream& stream, const SCA::data& data) {
    for (int i = 0; i < data.boneLinks.size(); i++)
      writeInt(stream, data.boneLinks[i]);
  }

  void SCA::writeBoneNames(std::ofstream& stream, const SCA::data& data) {
    char seperator = '\0';
    for (int i = 0; i < data.boneNames.size(); i++) {
      stream.write(data.boneNames[i].c_str(), data.boneNames[i].size());
      if (data.boneNames.size() - 1 != i)
        stream.write(&seperator, 1);
    }
  }

  void SCA::writePosition(std::ofstream& stream, const SCA::data& data) {
    writeFloat(stream, data.position[0]);
    writeFloat(stream, data.position[1]);
    writeFloat(stream, data.position[2]);
  }

  void SCA::writeRotation(std::ofstream& stream, const SCA::data& data) {
    writeFloat(stream, data.rotation[0]);
    writeFloat(stream, data.rotation[1]);
    writeFloat(stream, data.rotation[2]);
    writeFloat(stream, data.rotation[3]);
  }

  int SCA::writeAnimation(std::ofstream& stream, const SCA::data& data) {
    int framesize = 0;
    for (int i = 0; i < data.animation.size(); i++)
    {
      int start = stream.tellp();
      const frame& sub = data.animation[i];
      writeFloat(stream, sub.keytime);
      writeUInt(stream, sub.keyflags);

      for (int j = 0; j < sub.bones.size(); j++)
      {
        const bone& b  = sub.bones[i];

        writeFloat(stream,b.position[0]);
        writeFloat(stream,b.position[1]);
        writeFloat(stream,b.position[2]);
        writeFloat(stream,b.rotation[3]);
        writeFloat(stream,b.rotation[0]);
        writeFloat(stream,b.rotation[1]);
        writeFloat(stream,b.rotation[2]);
      }
      framesize = (int)stream.tellp() - start;
    }
    return framesize;
  }

  void SCA::writeString(std::ofstream& stream, const std::string& data) {
    stream.write(data.c_str(),data.length());
  }

  void SCA::writeInt(std::ofstream& stream, const int& value) {
    unsigned char bytes[4];
    bytes[0] = ((value >> 24) & 0xFF);
    bytes[1] = ((value >> 16) & 0xFF);
    bytes[2] = ((value >> 8) & 0xFF);
    bytes[3] = (value & 0xFF);
    stream.write((const char*)(bytes), 4);
  }

  void SCA::writeUInt(std::ofstream& stream, const unsigned int& value) {
    unsigned char bytes[4];
    bytes[0] = ((value >> 24) & 0xFF);
    bytes[1] = ((value >> 16) & 0xFF);
    bytes[2] = ((value >> 8) & 0xFF);
    bytes[3] = (value & 0xFF);
    stream.write((const char*)(bytes), 4);
  }

  void SCA::writeFloat(std::ofstream& stream, const float&data) {
    const float* a = &data;
    const int* b = (const int*)a;
    int    c = *b;
    writeInt(stream, data);
  }

}