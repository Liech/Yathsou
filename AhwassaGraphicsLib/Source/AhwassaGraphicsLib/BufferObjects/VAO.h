#pragma once

#include "VBO.h"

namespace Ahwassa {
  struct AttributeDescription;

  class VAO {
  public:
    VAO(IVBO* vbo);
    VAO(std::vector<IVBO*> vbo);
    virtual ~VAO();
    unsigned int getID()              const;
    void draw()                       const;
    void drawInstanced(size_t amount) const;

  protected:
    void init(const std::vector<std::vector<AttributeDescription>>&);
  private:
    unsigned int _id;
    unsigned int _size = 0;
    std::vector<IVBO*> _vbo;
  };
}
