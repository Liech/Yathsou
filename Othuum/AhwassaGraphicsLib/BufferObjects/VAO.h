#pragma once

#include "IVAO.h"
#include "Core/AttributeDescription.h"

namespace Ahwassa {
  template<typename Struct>
  class VAO : public IVAO
  {
  public:
    VAO(VBO<Struct>* vbo) : IVAO(vbo) {
      Struct s;
      init(s.getBinding());
    }
  private:
    VBO<Struct>* _vbo;
  };
}
