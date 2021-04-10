#pragma once

#include "AhwassaGraphicsLib/BufferObjects/IVAO.h"
#include "AhwassaGraphicsLib/Core/AttributeDescription.h"

namespace Ahwassa {
  template<typename Struct>
  class VAO : public IVAO
  {//todo: remove class
  public:
    VAO(IVBO* vbo) : IVAO({ vbo }) {
    }
  };
}
