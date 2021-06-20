#pragma once

#include <vector>
#include <fstream>

namespace Aezesel {
  class IO {
  protected:
    static void    writeString(std::ofstream&, const std::string&               );
    static void    writeInt   (std::ofstream&, const int&                       , bool endian = false);
    static void    writeUInt  (std::ofstream&, const unsigned int&              , bool endian = false);
    static void    writeFloat (std::ofstream&, const float&                     );
    static void    writeUShort(std::ofstream&, const unsigned short&            , bool endian = false);
    static void    write      (std::ofstream&, const std::vector<unsigned char>&);
            
    std::vector<unsigned char> read(const std::vector<unsigned char>&, size_t& position, size_t size);
    std::string    readString(const std::vector<unsigned char>&, size_t& position, size_t size);
    std::string    readString(const std::vector<unsigned char>&, size_t& position);
    int            readInt   (const std::vector<unsigned char>&, size_t& position);
    unsigned int   readUInt  (const std::vector<unsigned char>&, size_t& position);
    float          readFloat (const std::vector<unsigned char>&, size_t& position);
    unsigned short readUShort(const std::vector<unsigned char>&, size_t& position);

  };
}