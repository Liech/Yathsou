#pragma once

#include "Chunk.h"

//https://github.com/ephtracy/voxel-model/issues/19
namespace Aezesel {
  namespace MagicaVoxImporter {
    class ChunkrOBJ : public  Chunk {
    public:
      std::string getID() override { return "rOBJ"; }
      void        read(Reader own, Reader child) override;


    };
  }
}