#pragma once

#include <memory>
#include <vector>
#include <string>

namespace Aezesel {
  namespace MagicaVoxImporter {
    class Reader;
    class Chunk {
    public:
      virtual std::string    getID() = 0;
      virtual void           read(Reader own, Reader child);

      int                    numberOfChilds();
      std::shared_ptr<Chunk> getChild(int i);
      void                   addChild(std::shared_ptr<Chunk> newchild);

      virtual void           print(int indentation = 0);
    private:
      std::vector<std::shared_ptr<Chunk>> _childs;
    };
  }
}