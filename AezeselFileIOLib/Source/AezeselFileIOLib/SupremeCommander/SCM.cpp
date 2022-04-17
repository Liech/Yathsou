#include "SCM.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>
#include <nlohmann/json.hpp>

namespace Aezesel {
  SCM::data SCM::load(std::string filename)
  {

    std::ifstream input(filename, std::ios::binary);
    if (input.fail())
      throw std::runtime_error("Error opening " + filename);
    _buffer = std::vector<unsigned char>(std::istreambuf_iterator<char>(input), {});
    return loadInternal();
  }


  SCM::data SCM::load(const std::vector<unsigned char>& buffer) {
    _buffer = buffer;
    return loadInternal();
  }

  SCM::data SCM::loadInternal(){
    SCM::data result;
    _fileposition = 0;

    std::string marker = readString(_buffer, _fileposition, 4);
    int version = readInt(_buffer, _fileposition);
    int boneoffset = readInt(_buffer, _fileposition);
    int bonecount = readInt(_buffer, _fileposition);//unused
    int vertoffset = readInt(_buffer, _fileposition);
    int extravertoffset = readInt(_buffer, _fileposition); //unused
    int vertcount = readInt(_buffer, _fileposition);
    int indexoffset = readInt(_buffer, _fileposition);
    int indexcount = readInt(_buffer, _fileposition);
    int infooffset = readInt(_buffer, _fileposition);
    int infocount = readInt(_buffer, _fileposition);
    int totalbonecount = readInt(_buffer, _fileposition);

    if (marker != "MODL")
      throw std::runtime_error("File not scm");
    if (version != 5)
      throw std::runtime_error("Unsupported version");

    result.boneNames = readBoneNames(boneoffset);
    result.bones     = readBones(boneoffset, totalbonecount, result.boneNames);
    result.vertecies = readVertices(vertoffset, vertcount);
    result.indices   = readInidices(indexoffset, indexcount);
    result.info      = readInfo(infooffset, infocount);

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
    for (int i = 0; i < count / 3; i++)
    {
      tri subresult;
      subresult.a = readUShort(_buffer, _fileposition);
      subresult.b = readUShort(_buffer, _fileposition);
      subresult.c = readUShort(_buffer, _fileposition);
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
      subresult.position[0] = readFloat(_buffer, _fileposition);
      subresult.position[1] = readFloat(_buffer, _fileposition);
      subresult.position[2] = readFloat(_buffer, _fileposition);

      subresult.normal[0] = readFloat(_buffer, _fileposition);
      subresult.normal[1] = readFloat(_buffer, _fileposition);
      subresult.normal[2] = readFloat(_buffer, _fileposition);

      subresult.tangent[0] = readFloat(_buffer, _fileposition);
      subresult.tangent[1] = readFloat(_buffer, _fileposition);
      subresult.tangent[2] = readFloat(_buffer, _fileposition);

      subresult.binormal[0] = readFloat(_buffer, _fileposition);
      subresult.binormal[1] = readFloat(_buffer, _fileposition);
      subresult.binormal[2] = readFloat(_buffer, _fileposition);

      subresult.uv1[0] = readFloat(_buffer, _fileposition);
      subresult.uv1[1] = readFloat(_buffer, _fileposition);
      subresult.uv2[0] = readFloat(_buffer, _fileposition);
      subresult.uv2[1] = readFloat(_buffer, _fileposition);

      subresult.boneIndex[0] = _buffer[_fileposition + 0];
      subresult.boneIndex[1] = _buffer[_fileposition + 1];
      subresult.boneIndex[2] = _buffer[_fileposition + 2];
      subresult.boneIndex[3] = _buffer[_fileposition + 3];
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
      for (int i = 0; i < 16; i++)
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
      subResult.parentIndex = readInt(_buffer, _fileposition);
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

  nlohmann::json SCM::data::toJson() {
    nlohmann::json result;
    result["BoneNames"] = boneNames;
  
    nlohmann::json bon;
    for (auto b : bones) {
      nlohmann::json sub;
      sub["Name"] = b.name;
      std::vector<float> mat;
      for (int i = 0; i < 16; i++) {
        mat.push_back(glm::value_ptr(b.relativeInverseMatrix)[i]);
      }
      sub["RelativeInverseMatrix"] = mat;
      sub["Position"] = std::vector<float>{ b.rotation[0] , b.rotation[1] , b.rotation[2] };
      sub["Rotation"] = std::vector<float>{ b.rotation[0] , b.rotation[1] , b.rotation[2] , b.rotation[3] };
      sub["ParentIndex"] = b.parentIndex;
      bon.push_back(sub);
    }
    result["Bones"] = bon;
  
    nlohmann::json vert;
    for (auto v : vertecies) {
      nlohmann::json sub;
      sub["Binormal"] = std::vector<float>{ v.binormal[0], v.binormal[1], v.binormal[2] };
      sub["UV1"] = std::vector<float>{ v.uv1[0], v.uv1[1] };
      sub["UV2"] = std::vector<float>{ v.uv2[0], v.uv2[1] };
      sub["Normal"] = std::vector<float>{ v.normal[0], v.normal[1], v.normal[2] };
      sub["Tangent"] = std::vector<float>{ v.tangent[0], v.tangent[1], v.tangent[2] };
      sub["Position"] = std::vector<float>{ v.position[0], v.position[1], v.position[2] };
      sub["BoneIndex"] = v.boneIndex[0];
      vert.push_back(sub);
    }
    result["Vertecies"] = vert;
  
    nlohmann::json indi;
    for (auto i : indices)
      indi.push_back(std::vector<int>{i.a, i.b, i.c});
    result["Indices"] = indi;
    result["Info"] = info;
    return result;
  }
  
  void SCM::data::fromJson(const nlohmann::json&) {
  
  }

  void SCM::save(std::string filename, const SCM::data& data) {
    std::ofstream outfile(filename, std::ofstream::binary);

    writeString(outfile, "MODL");
    writeInt(outfile, 5);

    size_t boneOffsetPos = outfile.tellp();
    writeInt(outfile, 0); //boneoffset
    writeInt(outfile, data.bones.size());
    size_t vertexOffsetPos = outfile.tellp();
    writeInt(outfile, 0); //vertex offset
    writeInt(outfile, 0); //extravertoffset unused
    writeInt(outfile, data.vertecies.size());
    size_t indexOffsetPos = outfile.tellp();
    writeInt(outfile, 0); //indexoffset
    writeInt(outfile, data.indices.size() * 3);
    size_t infoOffsetPos = outfile.tellp();
    writeInt(outfile, 0); //infooffset
    writeInt(outfile, 0); //infocount ??
    writeInt(outfile, data.bones.size());

    writeBones(outfile, data);
    int boneOffset = outfile.tellp();
    writeBoneNames(outfile, data);
    
    int vertOffset = outfile.tellp();
    writeVertices(outfile, data);
    int indexOffset = outfile.tellp();
    writeInidices(outfile, data);
    int infoOffset = outfile.tellp();
    writeInfo(outfile, data);

    outfile.seekp(boneOffsetPos);
    writeInt(outfile, boneOffset);

    outfile.seekp(vertexOffsetPos);
    writeInt(outfile, vertOffset);
    
    outfile.seekp(indexOffsetPos);
    writeInt(outfile, indexOffset);
    
    outfile.seekp(infoOffsetPos);
    writeInt(outfile, infoOffset);
  }

  void SCM::writeBoneNames(std::ofstream& stream, const SCM::data& data) {
    char seperator = '\0';
    for (int i = 0; i < data.boneNames.size(); i++) {
      stream.write(data.boneNames[i].c_str(), data.boneNames[i].size());
      if (data.boneNames.size() - 1 != i)
        stream.write(&seperator, 1);
    }
  }

  void SCM::writeBones(std::ofstream& stream, const SCM::data& data) {
   for (int i = 0; i < data.bones.size(); i++)
    {
      const bone& sub = data.bones[i];
      const float* relInverse = (const float*)glm::value_ptr(sub.relativeInverseMatrix);
      for (int i = 0; i < 16; i++)
        writeFloat(stream, relInverse[i]);
      writeFloat(stream, sub.position[0]);
      writeFloat(stream, sub.position[1]);
      writeFloat(stream, sub.position[2]);
      writeFloat(stream, sub.rotation[0]);
      writeFloat(stream, sub.rotation[1]);
      writeFloat(stream, sub.rotation[2]);
      writeFloat(stream, sub.rotation[3]);
      int dummy = 0;
      writeInt(stream, dummy);
      writeInt(stream, sub.parentIndex);
      writeInt(stream, dummy);
      writeInt(stream, dummy);
    }
  }

  void SCM::writeVertices(std::ofstream& stream, const SCM::data& data) {
    for (int i = 0; i < data.vertecies.size(); i++)
    {
      const vertex& sub = data.vertecies[i];

      writeFloat(stream, sub.position[0]);
      writeFloat(stream, sub.position[1]);
      writeFloat(stream, sub.position[2]);

      writeFloat(stream, sub.tangent[0]);
      writeFloat(stream, sub.tangent[1]);
      writeFloat(stream, sub.tangent[2]);

      writeFloat(stream, sub.normal[0]);
      writeFloat(stream, sub.normal[1]);
      writeFloat(stream, sub.normal[2]);

      writeFloat(stream, sub.binormal[0]);
      writeFloat(stream, sub.binormal[1]);
      writeFloat(stream, sub.binormal[2]);

      writeFloat(stream, sub.uv1[0]);
      writeFloat(stream, sub.uv1[1]);
      writeFloat(stream, sub.uv2[0]);
      writeFloat(stream, sub.uv2[1]);

      stream.write((const char*)(&sub.boneIndex), 4);
    }
  }

  void SCM::writeInidices(std::ofstream& stream, const SCM::data& data) {
    for (int i = 0; i < data.indices.size(); i++)
    {
      const tri& sub = data.indices[i];
      writeUShort(stream,sub.a);
      writeUShort(stream,sub.b);
      writeUShort(stream,sub.c);
    }
  }

  void SCM::writeInfo(std::ofstream& stream, const SCM::data& data) {
    char seperator = '\0';
    for (int i = 0; i < data.info.size(); i++) {
      stream.write(data.info[i].c_str(), data.info[i].size());
      if (data.info.size() - 1 != i)
        stream.write(&seperator, 1);
    }
  }
}