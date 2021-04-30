#pragma once

#include <vector>
#include <fstream>

namespace Aezesel {
  class IO {
  protected:
    static void    writeString(std::ofstream&, const std::string&);
    static void    writeInt   (std::ofstream&, const int&);
    static void    writeUInt  (std::ofstream&, const unsigned int&);
    static void    writeFloat (std::ofstream&, const float&);
    static void    writeUShort(std::ofstream&, const unsigned short&);
                   
    std::string    readString(const std::vector<unsigned char>&, size_t& position, size_t size);
    std::string    readString(const std::vector<unsigned char>&, size_t& position);
    int            readInt   (const std::vector<unsigned char>&, size_t& position);
    unsigned int   readUInt  (const std::vector<unsigned char>&, size_t& position);
    float          readFloat (const std::vector<unsigned char>&, size_t& position);
    unsigned short readUShort(const std::vector<unsigned char>&, size_t& position);

  };
}