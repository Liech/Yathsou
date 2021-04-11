#pragma once

#include "Chunk.h"
namespace Aezesel {
  namespace MagicaVoxImporter {
    struct color {
      unsigned char r;
      unsigned char g;
      unsigned char b;
      unsigned char a;
    };


    class ChunkRGBA : public  Chunk {
    public:
      std::string getID() override { return "RGBA"; }
      void read(Reader own, Reader child) override;

      color palette[256];

      static std::shared_ptr<ChunkRGBA> getDefault();
    };
  }
}