#pragma once

#include <memory>
#include <array>
#include <vector>
#include <map>
#include <string>
#include "IyathuumCoreLib/BaseTypes/MultiDimensionalArray.h"

namespace Aezesel {
  namespace MagicaVoxImporter {
    class ChunkMAIN;

    class VoxFile {
    public:
      VoxFile(std::string filename);

      std::vector<std::shared_ptr<Iyathuum::MultiDimensionalArray<unsigned char, 3>>> Models;
      std::array<std::array<unsigned char, 4>, 256>       Colors;
      std::vector<std::map<std::string, std::string>>     Materials;
    };

  }
}