#pragma once

#include "VBO.h"

namespace Ahwassa {
  struct AttributeDescription;

  class IVAO {
  public:
    IVAO(IVBO* vbo);
    virtual ~IVAO();
    unsigned int getID();
    void draw();
    void drawInstanced(size_t amount);

  protected:
    void init(const std::vector<AttributeDescription>&);
  private:
    unsigned int _id;
    IVBO*        _vbo;
  };
}
