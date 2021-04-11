#include "ChunkFactory.h"
#include "Chunk.h"
#include <stdexcept>

//No fancy template factory. I hope it is easier to understand this way
#include "ChunkLAYR.h"
#include "ChunkMAIN.h"
#include "ChunkMATL.h"
#include "ChunknGRP.h"
#include "ChunknSHP.h"
#include "ChunknTRN.h"
#include "ChunkPACK.h"
#include "ChunkRGBA.h"
#include "ChunkSIZE.h"
#include "ChunkXYZI.h"
#include "ChunkrOBJ.h"

namespace Aezesel {
  namespace MagicaVoxImporter {
    std::shared_ptr<Chunk> ChunkFactory::make(std::string id) {
      if (id == "LAYR")
        return std::make_shared<ChunkLAYR>();
      else if (id == "MAIN")
        return std::make_shared<ChunkMAIN>();
      else if (id == "MATL")
        return std::make_shared<ChunkMATL>();
      else if (id == "nGRP")
        return std::make_shared<ChunknGRP>();
      else if (id == "nSHP")
        return std::make_shared<ChunknSHP>();
      else if (id == "nTRN")
        return std::make_shared<ChunknTRN>();
      else if (id == "PACK")
        return std::make_shared<ChunkPACK>();
      else if (id == "RGBA")
        return std::make_shared<ChunkRGBA>();
      else if (id == "SIZE")
        return std::make_shared<ChunkSIZE>();
      else if (id == "XYZI")
        return std::make_shared<ChunkXYZI>();
      else if (id == "rOBJ")
        return std::make_shared<ChunkrOBJ>();
      else
        throw std::runtime_error("Unkown ID: " + id);
    }
  }
}