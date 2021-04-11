#pragma once

#include "Chunk.h"
namespace Aezesel {
  namespace MagicaVoxImporter {
    class ChunkSIZE : public  Chunk {
    public:
      std::string getID() override { return "SIZE"; }
      void        read(Reader own, Reader child) override;
      void        print(int indentation = 0) override;

      int sizeX = 0;
      int sizeY = 0;
      int sizeZ = 0;
    };
  }
}