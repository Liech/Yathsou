#include "VoxFile.h"

#include <memory>

#include "ChunkMAIN.h"
#include "ChunkPACK.h"
#include "ChunkSIZE.h"
#include "ChunkXYZI.h"
#include "ChunkRGBA.h"
#include "ChunkMATL.h"

#include "Import.h"

namespace Aezesel {
  namespace MagicaVoxImporter {
    VoxFile::VoxFile(std::string filename) {
      Import Importer(filename);
      std::shared_ptr<ChunkMAIN> parsedFile = Importer._rawData;
      size_t currentChunk = 0;
      std::shared_ptr<ChunkPACK> pack = std::dynamic_pointer_cast<ChunkPACK>(parsedFile->getChild(currentChunk));
      int numberOfModels = 1;
      if (pack != nullptr) {
        numberOfModels = pack->numModels;
        currentChunk++;
      }

      for (int i = 0; i < numberOfModels; i++) {
        std::shared_ptr<ChunkSIZE> size = std::dynamic_pointer_cast<ChunkSIZE>(parsedFile->getChild(currentChunk));
        currentChunk++;
        std::shared_ptr<ChunkXYZI> xyzi = std::dynamic_pointer_cast<ChunkXYZI>(parsedFile->getChild(currentChunk));
        currentChunk++;
        std::shared_ptr<Iyathuum::MultiDimensionalArray<unsigned char, 3>> model = std::make_shared<Iyathuum::MultiDimensionalArray<unsigned char, 3>>(size->sizeX, size->sizeY, size->sizeZ);
        model->fill(0);
        for (int j = 0; j < xyzi->numVoxels; j++)
          model->getRef(xyzi->content[j].X, xyzi->content[j].Y, xyzi->content[j].Z) = xyzi->content[j].value;
        Models.push_back(model);
      }
      std::shared_ptr<ChunkRGBA> rgba = std::dynamic_pointer_cast<ChunkRGBA>(parsedFile->getChild(currentChunk));
      if (rgba == nullptr)
        rgba = ChunkRGBA::getDefault();
      else
        currentChunk++;
      for (int i = 0; i < 256; i++)
        Colors[i] = std::array<unsigned char, 4>{rgba->palette[i].r, rgba->palette[i].g, rgba->palette[i].b, rgba->palette[i].a};

      Materials.resize(256);
      while (currentChunk < parsedFile->numberOfChilds()) {
        std::shared_ptr<ChunkMATL> mat = std::dynamic_pointer_cast<ChunkMATL>(parsedFile->getChild(currentChunk));
        if (mat != nullptr) {
          Materials[mat->MaterialID] = mat->Properties;
        }
        currentChunk++;
      }

    }


  }
}