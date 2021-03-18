#include "Core/Serialization.h"

#include <fstream>
#include <filesystem>
#include <bitset>
#include <algorithm>

#include "VishalaNetworkLib/lib/xdelta3/xdelta3.h"

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
    unsigned char bytes[] = { data.data[data.position + 3],data.data[data.position + 2],data.data[data.position + 1],data.data[data.position] };
    int* pInt = (int*)bytes;
    int result = *pInt;
    data.position += 4;
    return result;
  }

  template<>
  void Serialization::val2bin<int>(BinaryPackage& data, int& value) {
    data.data.push_back((value >> 24) & 0xFF);
    data.data.push_back((value >> 16) & 0xFF);
    data.data.push_back((value >> 8) & 0xFF);
    data.data.push_back(value & 0xFF);
  }

  template <>
  size_t Serialization::bin2val<size_t>(BinaryPackage& data) {
    size_t size = sizeof(size_t);
    std::vector<unsigned char> sub = std::vector<unsigned char>(data.data.begin() + data.position, data.data.begin() + data.position + size);
    size_t* cast = reinterpret_cast<size_t*>(sub.data());
    data.position += size;
    size_t result = *cast;
    return result;
  }

  template<>
  void Serialization::val2bin<size_t>(BinaryPackage& data, size_t& value) {
    unsigned char const* c = reinterpret_cast<unsigned char const*>(value);
    size_t size = sizeof(size_t);
    data.data.insert(data.data.end(), c, c + size);
  }

  template<>
  void Serialization::val2bin<bool>(BinaryPackage& data, bool& value) {
    int v = value ? 1 : 0;
    val2bin(data, v);
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

  template <>
  bool Serialization::bin2val<bool>(BinaryPackage& data) {
    int  a = bin2val<int>(data);
    return a!=0;
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

  BinaryPackage Serialization::createDelta(const BinaryPackage& oldData, const BinaryPackage& newData){
    const size_t reservedSize = newData.data.size()<1024?1024: newData.data.size();
    BinaryPackage result;
    result.data.resize(reservedSize);
    usize_t usedSize = 0;
    int errorCode = xd3_encode_memory(newData.data.data(), newData.data.size(), oldData.data.data(), oldData.data.size(), result.data.data(), &usedSize, reservedSize, 0);
    
    result.position = usedSize;
    size_t len = newData.data.size();
    val2bin<size_t>(result, len);
    result.position = 0;
    result.data.resize(usedSize + sizeof(size_t));
    return result;
  }

  BinaryPackage Serialization::applyDelta(const BinaryPackage& oldData, BinaryPackage& delta) {
    size_t oldDeltaData = oldData.position;
    delta.position = oldData.data.size() - sizeof(size_t);
    size_t newSize = bin2val<size_t>(delta);
    delta.position = oldDeltaData;

    BinaryPackage result;
    result.data.resize(newSize);
    size_t actualNewSize = 0;

    xd3_decode_memory(delta.data.data(), delta.data.size(), oldData.data.data(), oldData.data.size() - sizeof(size_t), result.data.data(), &actualNewSize, newSize, 0);
    if (actualNewSize != newSize)
      throw std::runtime_error("Decrompress error");

    return result;
  }
}