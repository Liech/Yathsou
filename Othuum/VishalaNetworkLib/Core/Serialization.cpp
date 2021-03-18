#include "Core/Serialization.h"

#include <fstream>
#include <filesystem>
#include <bitset>
#include <algorithm>

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
}