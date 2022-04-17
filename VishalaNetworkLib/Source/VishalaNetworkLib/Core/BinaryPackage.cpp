#include "BinaryPackage.h"

#include <bitset>
#include <fstream>

#include <xdelta3/xdelta3.h>
#include <snappy.h>
#include "Core/Serialization.h"

namespace Vishala {
  void BinaryPackage::add(BinaryPackage package) {
    data.insert(data.begin() + position, package.data.begin(), package.data.end());    
    position += package.data.size();
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
  void BinaryPackage::val2bin<size_t>(BinaryPackage& data, const size_t& value) {    
    if (data.data.size() < data.position + 8)
      data.data.resize(data.position + 8);
    data.data[data.position + 0] = ((value >> 56) & 0xFFFF);
    data.data[data.position + 1] = ((value >> 48) & 0xFFFF);
    data.data[data.position + 2] = ((value >> 40) & 0xFFFF);
    data.data[data.position + 3] = ((value >> 32) & 0xFFFF);
    data.data[data.position + 4] = ((value >> 24) & 0xFFFF);
    data.data[data.position + 5] = ((value >> 16) & 0xFFFF);
    data.data[data.position + 6] = ((value >> 8)  & 0xFFFF);
    data.data[data.position + 7] = (value         & 0xFFFF);
    data.position += 8;
  }

  template<>
  void BinaryPackage::val2bin<int>(BinaryPackage& data, const int& value) {
    if (data.data.size() < data.position + 4)
      data.data.resize(data.position + 4);
    data.data[data.position + 0] = ((value >> 24) & 0xFF);
    data.data[data.position + 1] = ((value >> 16) & 0xFF);
    data.data[data.position + 2] = ((value >> 8) & 0xFF);
    data.data[data.position + 3] = (value & 0xFF);
    data.position += 4;
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
  void BinaryPackage::val2bin<char>(BinaryPackage& data, const char& value) {
    if (data.position == data.data.size())
      data.data.push_back((unsigned char)value);
    else
      data.data[data.position] = (unsigned char)value;
    data.position++;
  }

  template <>
  char BinaryPackage::bin2val<char>(BinaryPackage& data) {
    char result = data.data[data.position];
    data.position += 1;
    return result;
  }

  template<>
  void BinaryPackage::val2bin<unsigned char>(BinaryPackage& data, const unsigned char& value) {
    if (data.position == data.data.size())
      data.data.push_back(value);
    else
      data.data[data.position] = value;
    data.position++;
  }

  template <>
  unsigned char BinaryPackage::bin2val<unsigned char>(BinaryPackage& data) {
    unsigned char result = data.data[data.position];
    data.position += 1;
    return result;
  }

  template<>
  void BinaryPackage::val2bin<bool>(BinaryPackage& data,const bool& value) {
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
  void BinaryPackage::val2bin<std::string>(BinaryPackage& data,const std::string& value) {
    int len = value.length();
    val2bin<int>(data, len);
    data.data.insert(data.data.end(), value.data(), value.data() + len);
    data.position += value.length();
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
  void BinaryPackage::val2bin<float>(BinaryPackage& data,const float& value) {
    const float* a = &value;
    const int* b = (const int*)a;
    int    c = *b;
    val2bin<int>(data, c);
  }

  BinaryPackage BinaryPackage::createDelta(const BinaryPackage& oldData, const BinaryPackage& newData) {
    const size_t reservedSize = newData.data.size()-newData.position < 1024 ? 1024 : newData.data.size()-newData.position;
    BinaryPackage result;
    size_t headerSize = sizeof(size_t);
    result.position = headerSize;
    result.data.resize(reservedSize + headerSize);
    usize_t usedSize = 0;
    int errorCode = xd3_encode_memory(newData.data.data() + newData.position, newData.data.size() - newData.position, oldData.data.data() + oldData.position, oldData.data.size() - oldData.position, result.data.data() + result.position, &usedSize, reservedSize, 0);
    if (errorCode != 0)
      throw std::runtime_error("Something went wrong while creating delta");
    size_t len = newData.data.size() - newData.position;
    result.data.resize(usedSize + headerSize);
    result.position = 0;
    val2bin<size_t>(result, len);
    result.position = 0;
    return result;
  }

  BinaryPackage BinaryPackage::applyDelta(const BinaryPackage& oldData, BinaryPackage& delta) {
    size_t oldDeltaData = oldData.position;
    size_t newSize = bin2val<size_t>(delta);

    BinaryPackage result;
    result.data.resize(newSize);
    size_t actualNewSize = newSize;

    int errorCode = xd3_decode_memory(delta.data.data() + delta.position, delta.data.size() - delta.position, oldData.data.data() + oldData.position, oldData.data.size() - oldData.position, result.data.data(), &actualNewSize, newSize, 0);
    if (errorCode != 0 || actualNewSize != newSize)
      throw std::runtime_error("Something went wrong while applying delta");

    return result;
  }

  BinaryPackage BinaryPackage::compress() {
    std::string input(data.begin() + position, data.end());
    std::string output;
    snappy::Compress(input.data(), input.size(), &output);
    BinaryPackage result;
    result.data.resize(output.size());
    std::copy(output.begin(), output.end(), result.data.data());
    return result;
  }

  BinaryPackage BinaryPackage::decompress() {
    std::string input(data.begin()+position, data.end());
    std::string output;
    snappy::Uncompress(input.data(), input.size(), &output);
    BinaryPackage result;
    result.data.resize(output.size());
    std::copy(output.begin(), output.end(), result.data.data());
    return result;
  }

}