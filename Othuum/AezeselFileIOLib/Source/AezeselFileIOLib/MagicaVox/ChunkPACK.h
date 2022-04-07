#pragma once

#include "Chunk.h"
namespace Aezesel {
  namespace MagicaVoxImporter {
    class ChunkPACK : public  Chunk {
    public:
      std::string getID() override { return "PACK"; }
      void read(Reader own, Reader child) override;

      int numModels = 0;
    };
  }
}