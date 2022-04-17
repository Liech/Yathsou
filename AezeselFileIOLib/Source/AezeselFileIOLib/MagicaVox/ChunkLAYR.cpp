#include "ChunkLAYR.h"

#include "Reader.h"

namespace Aezesel {
  namespace MagicaVoxImporter {
    void ChunkLAYR::read(Reader own, Reader child) {
      Chunk::read(own, child);

      LayerID = own.readInt();
      Attributes = own.readDict();
      own.readInt(); //reserved stuff
    }
  }
}