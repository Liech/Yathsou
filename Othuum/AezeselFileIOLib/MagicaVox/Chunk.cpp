#include "Chunk.h"

#include "Reader.h"
#include "ChunkFactory.h"

#include <iostream>

namespace Aezesel {
  namespace MagicaVoxImporter {
    void Chunk::read(Reader own, Reader child) {
      //handle children
      while (!child.endOfBufferReached()) {
        addChild(child.readChunk());
      }
    }

    int Chunk::numberOfChilds() {
      return _childs.size();
    }

    std::shared_ptr<Chunk> Chunk::getChild(int i) {
      return _childs[i];
    }

    void Chunk::addChild(std::shared_ptr<Chunk> newchild) {
      _childs.push_back(newchild);
    }

    void Chunk::print(int indentation) {
      std::cout << std::string(indentation, ' ') << getID() << std::endl;
      for (int i = 0; i < _childs.size(); i++)
        _childs[i]->print(indentation + 1);
    }
  }
}