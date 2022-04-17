#include "ChunkXYZI.h"
#include "Reader.h"

#include <iostream>
#include <string>

namespace Aezesel {
  namespace MagicaVoxImporter {
    void ChunkXYZI::read(Reader own, Reader child) {
      Chunk::read(own, child);
      numVoxels = own.readInt();
      content.resize(numVoxels);

      for (int i = 0; i < numVoxels; i++) {
        voxel current;
        std::vector<unsigned char> voxelContent = own.readChars(4);
        current.X = voxelContent[0];
        current.Y = voxelContent[1];
        current.Z = voxelContent[2];
        current.value = voxelContent[3];
        content[i] = current;
      }
    }


    void ChunkXYZI::print(int indentation) {
      Chunk::print(indentation);
      std::cout << std::string(indentation + 1, ' ') << content.size() << std::endl;
    }
  }
}