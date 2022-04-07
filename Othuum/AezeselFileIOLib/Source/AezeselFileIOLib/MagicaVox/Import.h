#pragma once

#include <string>
#include <memory>
#include "Chunk.h"
#include "ChunkMAIN.h"

namespace Aezesel {
  namespace MagicaVoxImporter {
    class Import {
    public:
      Import(std::string filename);
      std::shared_ptr<ChunkMAIN> _rawData;
    };
  }
}