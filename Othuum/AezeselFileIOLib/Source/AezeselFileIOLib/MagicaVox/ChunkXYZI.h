#pragma once

#include "Chunk.h"

namespace Aezesel {
  namespace MagicaVoxImporter {
    struct voxel {
      unsigned char X;
      unsigned char Y;
      unsigned char Z;
      unsigned char value;
    };

    class ChunkXYZI : public  Chunk {
    public:
      std::string getID() override { return "XYZI"; }
      void        read(Reader own, Reader child) override;
      void        print(int indentation = 0) override;

      int                numVoxels = 0;
      std::vector<voxel> content;
    };
  }
}