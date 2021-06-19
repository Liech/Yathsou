#include "IO.h"


namespace Aezesel {
  float IO::readFloat(const std::vector<unsigned char>& data, size_t& position)
  {
    int  a = readInt(data, position);
    int* b = &a;
    float* c = (float*)b;
    return *c;
  }

  int IO::readInt(const std::vector<unsigned char>& data, size_t& position)
  {
    unsigned char bytes[] = { data[position],data[position + 1],data[position + 2],data[position + 3] };
    int* pInt = (int*)bytes;
    int result = *pInt;
    position += 4;
    return result;
  }

  unsigned int IO::readUInt(const std::vector<unsigned char>& data, size_t& position)
  {
    unsigned char bytes[] = { data[position],data[position + 1],data[position + 2],data[position + 3] };
    unsigned int* pInt = (unsigned int*)bytes;
    unsigned int result = *pInt;
    position += 4;
    return result;
  }

  std::string IO::readString(const std::vector<unsigned char>& data, size_t& position, size_t size)
  {
    char* d = (char*)data.data() + position;
    position += size;
    return std::string(d, size);
  }

  std::string IO::readString(const std::vector<unsigned char>& data, size_t& position)
  {
    char* start = (char*)data.data() + position;
    //auto debug = std::vector<unsigned char>(data.begin() + position - 20, data.begin() + position + 40);
    int i = 0;
    while (i < 10000) {
      unsigned char c = *(start + i);
      if (c == '\0')
        break;
      i++;
    }
    std::string result(start,i);
    position += result.size()+1;
    return result;
  }

  void IO::writeString(std::ofstream& stream, const std::string& data) {
    stream.write(data.c_str(), data.length());
  }

  void IO::writeInt(std::ofstream& stream, const int& value) {
    unsigned char bytes[4];
    bytes[0] = ((value >> 24) & 0xFF);
    bytes[1] = ((value >> 16) & 0xFF);
    bytes[2] = ((value >> 8) & 0xFF);
    bytes[3] = (value & 0xFF);
    stream.write((const char*)(bytes), 4);
  }

  void IO::writeUInt(std::ofstream& stream, const unsigned int& value) {
    unsigned char bytes[4];
    bytes[0] = ((value >> 24) & 0xFF);
    bytes[1] = ((value >> 16) & 0xFF);
    bytes[2] = ((value >> 8) & 0xFF);
    bytes[3] = (value & 0xFF);
    stream.write((const char*)(bytes), 4);
  }

  void IO::writeFloat(std::ofstream& stream, const float& data) {
    const float* a = &data;
    const int* b = (const int*)a;
    int    c = *b;
    writeInt(stream, data);
  }

  unsigned short IO::readUShort(const std::vector<unsigned char>& data, size_t& position)
  {
    unsigned char bytes[] = { data[position],data[position + 1] };
    unsigned short* pInt = (unsigned short*)bytes;
    unsigned short result = *pInt;
    position += 2;
    return result;
  }

  void IO::writeUShort(std::ofstream& stream, const unsigned short& data) {
    unsigned short* p = (unsigned short*)data;
    stream.write((const char*)p, sizeof(unsigned short));
  }

  std::vector<unsigned char> IO::read(const std::vector<unsigned char>& data, size_t& position, size_t size) {
    std::vector<unsigned char> result(data.begin() + position, data.begin() + position + size);    
    position += size;
    return result;
  }
}