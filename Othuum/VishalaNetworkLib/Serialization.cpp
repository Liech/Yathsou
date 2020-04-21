#include "Serialization.h"

#include <fstream>
#include <filesystem>

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
}