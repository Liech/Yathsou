#pragma once

#include "Chunk.h"
#include <map>

namespace Aezesel {
  namespace MagicaVoxImporter {
    class ChunknSHP : public  Chunk {
    public:
      std::string getID() override { return "nSHP"; }
      void        read(Reader own, Reader child) override;

      int                                                             ID;
      std::map<std::string, std::string>                              Attributes;
      std::vector<std::pair<int, std::map<std::string, std::string>>> Models;
    };
  }
}