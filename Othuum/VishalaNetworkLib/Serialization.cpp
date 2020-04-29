#include "Serialization.h"

#include <fstream>
#include <filesystem>
#include <bitset>

namespace Vishala {
  void Serialization::toBinFile(std::string filename) {
    BinaryPackage data = toBinary();
    std::ofstream stream;
    stream.open(filename);
    stream << data.data.data();
    stream.close();
  }

  void Serialization::fromBinFile(std::string filename) {
    if (!std::filesystem::exists(filename)) {
      toBinFile(filename);
      return;
    }

    std::ifstream inputStream(filename);
    BinaryPackage data;
    data.data = std::vector<unsigned char>((std::istreambuf_iterator<char>(inputStream)), std::istreambuf_iterator<char>());
    inputStream.close();
    fromBinary(data);
  }  

  void Serialization::toJsonFile(std::string filename) {
    std::ofstream stream;
    stream.open(filename);
    nlohmann::json j = toJson();
    stream << j.dump(4);
    stream.close();
  }

  void Serialization::fromJsonFile(std::string filename) {
    if (!std::filesystem::exists(filename)) {
      toJsonFile(filename);
      return;
    }
    std::ifstream inputStream(filename);
    std::string content((std::istreambuf_iterator<char>(inputStream)), std::istreambuf_iterator<char>());
    inputStream.close();
    fromJson(nlohmann::json::parse(content));
  }


  template <>
  int Serialization::bin2val<int>(BinaryPackage& data) {
    unsigned char bytes[] = { data.data[data.position+3],data.data[data.position+2],data.data[data.position+1],data.data[data.position]  };
    int* pInt = (int*)bytes;
    int result = *pInt;
    data.position += 4;
    return result;
  }

  template<>
  void Serialization::val2bin<int>(BinaryPackage& data, int& value) {
    data.data.push_back((value >> 24) & 0xFF);
    data.data.push_back((value >> 16) & 0xFF);
    data.data.push_back((value >> 8)  & 0xFF);
    data.data.push_back( value        & 0xFF);
  }

  template <>
  std::string Serialization::bin2val<std::string>(BinaryPackage& data) {
    int len = bin2val<int>(data);    
    char* d = (char*)data.data.data() + data.position;
    std::string result = std::string(d, len);
    data.position += len;
    return result;
  }

  template<>
  void Serialization::val2bin<std::string>(BinaryPackage& data, std::string& value) {
    int len = value.length();
    val2bin<int>(data, len);
    data.data.insert(data.data.end(), value.data(), value.data() + len);
  }

  template <>
  float Serialization::bin2val<float>(BinaryPackage& data) {
    int  a = bin2val<int>(data);
    int* b = &a;
    float* c = (float*)b;
    return *c;
  }

  template<>
  void Serialization::val2bin<float>(BinaryPackage& data, float& value) {
    float* a = &value;
    int*   b = (int*)a;
    int    c = *b;
    val2bin<int>(data,c);
  }

  template<>
  void Serialization::val2bin<Serialization*>(BinaryPackage& data, Serialization*& value) {
    auto result = value->toBinary();
    data.data.insert(data.data.end(), result.data.begin(), result.data.end());
  }


}