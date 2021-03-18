#include "BinaryPackage.h"

#include <bitset>
#include <fstream>

#include "VishalaNetworkLib/lib/xdelta3/xdelta3.h"
#include "VishalaNetworkLib/Core/Serialization.h"

namespace Vishala {
  void BinaryPackage::add(BinaryPackage package) {
    data.insert(data.end(), package.data.begin(), package.data.end());
  }

  template <>
  size_t BinaryPackage::bin2val<size_t>(BinaryPackage& data) {
    unsigned char bytes[] = { 
      data.data[data.position + 7],data.data[data.position + 6],data.data[data.position + 5],data.data[data.position+4],
      data.data[data.position + 3],data.data[data.position + 2],data.data[data.position + 1],data.data[data.position]
    };
    size_t* pInt = (size_t*)bytes;
    size_t result = *pInt;
    data.position += 8;
    return result;
  }

  template<>
  void BinaryPackage::val2bin<size_t>(BinaryPackage& data, size_t& value) {    
    data.data.push_back((value >> 56) & 0xFFFF);
    data.data.push_back((value >> 48) & 0xFFFF);
    data.data.push_back((value >> 40) & 0xFFFF);
    data.data.push_back((value >> 32) & 0xFFFF);
    data.data.push_back((value >> 24) & 0xFFFF);
    data.data.push_back((value >> 16) & 0xFFFF);
    data.data.push_back((value >> 8)  & 0xFFFF);
    data.data.push_back(value         & 0xFFFF);
  }

  template<>
  void BinaryPackage::val2bin<int>(BinaryPackage& data, int& value) {
    data.data.push_back((value >> 24) & 0xFF);
    data.data.push_back((value >> 16) & 0xFF);
    data.data.push_back((value >> 8) & 0xFF);
    data.data.push_back(value & 0xFF);
  }

  template <>
  int BinaryPackage::bin2val<int>(BinaryPackage& data) {
    unsigned char bytes[] = { data.data[data.position + 3],data.data[data.position + 2],data.data[data.position + 1],data.data[data.position] };
    int* pInt = (int*)bytes;
    int result = *pInt;
    data.position += 4;
    return result;
  }

  template<>
  void BinaryPackage::val2bin<bool>(BinaryPackage& data, bool& value) {
    int v = value ? 1 : 0;
    val2bin(data, v);
  }

  template <>
  std::string BinaryPackage::bin2val<std::string>(BinaryPackage& data) {
    int len = bin2val<int>(data);
    char* d = (char*)data.data.data() + data.position;
    std::string result = std::string(d, len);
    data.position += len;
    return result;
  }

  template<>
  void BinaryPackage::val2bin<std::string>(BinaryPackage& data, std::string& value) {
    int len = value.length();
    val2bin<int>(data, len);
    data.data.insert(data.data.end(), value.data(), value.data() + len);
  }

  template <>
  float BinaryPackage::bin2val<float>(BinaryPackage& data) {
    int  a = bin2val<int>(data);
    int* b = &a;
    float* c = (float*)b;
    return *c;
  }

  template <>
  bool BinaryPackage::bin2val<bool>(BinaryPackage& data) {
    int  a = bin2val<int>(data);
    return a != 0;
  }

  template<>
  void BinaryPackage::val2bin<float>(BinaryPackage& data, float& value) {
    float* a = &value;
    int* b = (int*)a;
    int    c = *b;
    val2bin<int>(data, c);
  }

  template<>
  void BinaryPackage::val2bin<Serialization*>(BinaryPackage& data, Serialization*& value) {
    auto result = value->toBinary();
    data.data.insert(data.data.end(), result.data.begin(), result.data.end());
  }

  BinaryPackage BinaryPackage::createDelta(const BinaryPackage& oldData, const BinaryPackage& newData) {
    const size_t reservedSize = newData.data.size() < 1024 ? 1024 : newData.data.size();
    BinaryPackage result;
    result.data.resize(reservedSize);
    usize_t usedSize = 0;
    int errorCode = xd3_encode_memory(newData.data.data(), newData.data.size(), oldData.data.data(), oldData.data.size(), result.data.data(), &usedSize, reservedSize, 0);
    if (errorCode != 0)
      throw std::runtime_error("Something went wrong while creating delta");
    result.position = usedSize;
    size_t len = newData.data.size();
    result.data.resize(usedSize);
    val2bin<size_t>(result, len);
    result.position = 0;
    return result;
  }

  BinaryPackage BinaryPackage::applyDelta(const BinaryPackage& oldData, BinaryPackage& delta) {
    size_t oldDeltaData = oldData.position;
    delta.position = delta.data.size() - sizeof(size_t);
    size_t newSize = bin2val<size_t>(delta);
    delta.position = oldDeltaData;

    BinaryPackage result;
    result.data.resize(newSize);
    size_t actualNewSize = newSize;

    int errorCode = xd3_decode_memory(delta.data.data(), delta.data.size() - sizeof(size_t), oldData.data.data(), oldData.data.size() , result.data.data(), &actualNewSize, newSize, 0);
    if (errorCode != 0 || actualNewSize != newSize)
      throw std::runtime_error("Something went wrong while applying delta");

    return result;
  }
}