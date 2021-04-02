#pragma once

#include "VBO.h"
#include "AttributeDescription.h"

namespace Ahwassa {

  class IVAO {
  public:
    IVAO(IVBO* vbo);
    virtual ~IVAO();
    unsigned int getID();
    void bind();

  protected:
    void init(const std::vector<AttributeDescription>&);
  private:
    unsigned int _id;
    IVBO*        _vbo;
  };

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
