#pragma once

#include "Chunk.h"
#include <map>

namespace Aezesel {
  namespace MagicaVoxImporter {
    class ChunknGRP : public Chunk {
    public:
      std::string getID() override { return "nGRP"; }
      void        read(Reader own, Reader child) override;


      int                                ID;
      std::map<std::string, std::string> Attributes;
      std::vector<int>                   ChildNodes;
    };
  }
}