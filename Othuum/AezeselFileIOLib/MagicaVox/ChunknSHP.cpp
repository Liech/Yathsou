#include "ChunknSHP.h"

#include "Reader.h"

namespace Aezesel {
  namespace MagicaVoxImporter {

    void ChunknSHP::read(Reader own, Reader child) {
      Chunk::read(own, child);
      ID = own.readInt();
      Attributes = own.readDict();
      int numberOfModels = own.readInt();
      Models.resize(numberOfModels);
      for (int i = 0; i < numberOfModels; i++) {
        int id = own.readInt();
        auto attr = own.readDict();
        Models[i] = std::make_pair(id, attr);
      }
    }
  }
}