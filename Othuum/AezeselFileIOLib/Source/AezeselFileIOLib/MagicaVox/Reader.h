#pragma once

#include <vector>
#include <memory>
#include <map>
#include <string>

namespace Aezesel {
  namespace MagicaVoxImporter {
    class Chunk;

    struct Rotation {
      int v00 = 0, v10 = 0, v20 = 0;
      int v01 = 0, v11 = 0, v21 = 0;
      int v02 = 0, v12 = 0, v22 = 0;
    };

    class Reader {
    public:
      Reader(std::vector<unsigned char> content);
      Reader() {}
      Reader read(size_t numberOfBytes);
      std::vector<unsigned char> readChars(size_t numberOfBytes);
      std::string readChunkID();
      int         readInt();
      std::shared_ptr<Chunk> readChunk();
      bool endOfBufferReached();
      std::string readString();
      std::map<std::string, std::string> readDict();
      Rotation readRotation();

    private:
      size_t                     _currentPosition = 0;
      std::vector<unsigned char> _content;

      void assertCanRead();
    };
  }
}