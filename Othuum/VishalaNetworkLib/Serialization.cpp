#include "Serialization.h"

#include <fstream>
#include <filesystem>
#include <bitset>

namespace Vishala {
  void Serialization::toBinFile(std::string filename) {
    std::vector<unsigned char> data = toBinary();
    std::ofstream stream;
    stream.open(filename);
    stream << data.data();
    stream.close();
  }

  void Serialization::fromBinFile(std::string filename) {
    if (!std::filesystem::exists(filename)) {
      toBinFile(filename);
      return;
    }

    std::ifstream inputStream(filename);
    std::vector<unsigned char> content((std::istreambuf_iterator<char>(inputStream)), std::istreambuf_iterator<char>());
    inputStream.close();
    fromBinary(content,0);
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
  int Serialization::bin2val<int>(std::vector<unsigned char>& data, size_t& position) {
    unsigned char bytes[] = { data[position],data[position+1],data[position+2],data[position+3]  };
    int* pInt = (int*)bytes;
    int result = *pInt;
    position += 4;
    return result;
  }

  template<>
  void Serialization::val2bin<int>(std::vector<unsigned char>& data, int& value) {
    data.push_back((value >> 24) & 0xFF);
    data.push_back((value >> 16) & 0xFF);
    data.push_back((value >> 8)  & 0xFF);
    data.push_back( value        & 0xFF);
  }

  template <>
  std::string Serialization::bin2val<std::string>(std::vector<unsigned char>& data, size_t& position) {
    return std::string((char*)data.data(), data.size());
  }

  template<>
  void Serialization::val2bin<std::string>(std::vector<unsigned char>& data, std::string& value) {
    data.insert(data.end(), value.data(), value.data() + value.length() + 1);
  }

  template <>
  float Serialization::bin2val<float>(std::vector<unsigned char>& data, size_t& position) {
    int  a = bin2val<int>(data, position);
    int* b = &a;
    float* c = (float*)b;
    return *c;
  }

  template<>
  void Serialization::val2bin<float>(std::vector<unsigned char>& data, float& value) {
    float* a = &value;
    int*   b = (int*)a;
    int    c = *b;
    val2bin<int>(data,c);
  }

  template<>
  void Serialization::val2bin<Serialization*>(std::vector<unsigned char>& data, Serialization*& value) {
    auto result = value->toBinary();
    data.insert(data.end(), result.begin(), result.end());
  }


}