#include "ChunkrOBJ.h"

#include "Reader.h"

namespace Aezesel {
  namespace MagicaVoxImporter {
    void ChunkrOBJ::read(Reader own, Reader child) {
      Chunk::read(own, child);
    }
  }
}