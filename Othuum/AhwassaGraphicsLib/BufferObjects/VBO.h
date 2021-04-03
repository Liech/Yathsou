#pragma once

#include <vector>
#include <stdexcept>

#include "AhwassaGraphicsLib/BufferObjects/IVBO.h"

namespace Ahwassa{
  template<typename Struct>
  class VBO : public IVBO
  {
  public:
    VBO(std::vector<Struct> content) : IVBO(content.size(), sizeof(Struct),content.data())
    {
    }

    ~VBO()
    {
    }

    void setData(std::vector<Struct> content) {
      if (getSize() != content.size())
        throw std::runtime_error("Size different");
      setRawData(content.data(), content.size());
    }
  };
}
