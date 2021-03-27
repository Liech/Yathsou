#include "Core/Serialization.h"

#include <fstream>
#include <filesystem>
#include <bitset>
#include <algorithm>
#include "IyathuumCoreLib/Util/ConstExprHash.h"

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

  BinaryPackage Serialization::serialize() const{    
    Vishala::BinaryPackage result;
    size_t id = ID();
    Vishala::BinaryPackage::val2bin(result, id);
    result.add(toBinary());
    return result;
  }

  std::shared_ptr<Serialization> Serialization::deserialize(BinaryPackage& Package) {
    size_t id = Vishala::BinaryPackage::bin2val<size_t>(Package);
    auto result = Iyathuum::Factory<Serialization>::make(id2name[id]);
    result->fromBinary(Package);
    return result;
  }

  nlohmann::json Serialization::serializeJson() const{
    nlohmann::json result = toJson();    
    result["___ID___"] = Name();
    return result;
  }

  std::shared_ptr<Serialization> Serialization::deserializeJson(nlohmann::json j) {
    auto result = Iyathuum::Factory<Serialization>::make(j["___ID___"]);
    result->fromJson(j);
    return result;
  }

  constexpr const size_t Serialization::ID() const
  {
    return constexprHASH(Name());
  }
}