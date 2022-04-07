#pragma once
#include <array>

#include "Chunk.h"

namespace Aezesel {
  namespace MagicaVoxImporter {
    class ChunknTRN : public  Chunk {
    public:
      std::string getID() override { return "nTRN"; }
      void        read(Reader own, Reader child) override;

      int                ID;
      std::string        Name;
      bool               Hidden;
      int                ChildID;
      int                LayerID;
      std::string        Rotation = ""; //unfinished here
      std::string        Translation;  //unfinished here
    };
  }
}