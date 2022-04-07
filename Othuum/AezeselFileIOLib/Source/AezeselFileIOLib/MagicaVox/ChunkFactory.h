#pragma once

#include <memory>
#include <string>


namespace Aezesel {
  namespace MagicaVoxImporter {
    class Chunk;
    class ChunkFactory {
    public:
      static std::shared_ptr<Chunk> make(std::string id);
    };
  }
}