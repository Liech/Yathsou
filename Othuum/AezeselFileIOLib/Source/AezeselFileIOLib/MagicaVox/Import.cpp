#include "Import.h"

#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>


#include "Reader.h"

namespace Aezesel {
  namespace MagicaVoxImporter {
    Import::Import(std::string filename) {
      std::ifstream input(filename, std::ios::binary);
      if (input.fail())
        throw std::runtime_error("Error opening " + filename);
      std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), {});

      Reader content(buffer);
      std::string magicByte = content.readChunkID();
      if (magicByte != "VOX ")
        throw std::runtime_error("Magic Byte not found!");
      int version = content.readInt();
      if (version != 150)
        throw std::runtime_error("Im not sure that i can handle this version");
      std::shared_ptr<ChunkMAIN> raw = std::dynamic_pointer_cast<ChunkMAIN>(content.readChunk());
      _rawData = raw;
      _rawData->print();
    }


  }
}