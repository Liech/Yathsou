#include "ChunknGRP.h"

#include "Reader.h"

namespace Aezesel {
  namespace MagicaVoxImporter {
    void ChunknGRP::read(Reader own, Reader child) {
      Chunk::read(own, child);

      ID = own.readInt();
      Attributes = own.readDict();
      int numberOfChildren = own.readInt();
      ChildNodes.clear();
      ChildNodes.resize(numberOfChildren);
      for (int i = 0; i < numberOfChildren; i++)
        ChildNodes[i] = own.readInt();
    }
  }
}