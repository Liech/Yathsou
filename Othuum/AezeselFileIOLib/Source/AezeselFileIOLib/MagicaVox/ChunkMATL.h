#pragma once

#include "Chunk.h"
#include <map>

namespace Aezesel {
  namespace MagicaVoxImporter {
    class ChunkMATL : public Chunk {
    public:
      std::string getID() override { return "MATL"; }
      void        read(Reader own, Reader child) override;

      int MaterialID;
      std::map<std::string, std::string> Properties;
    };
  }
}