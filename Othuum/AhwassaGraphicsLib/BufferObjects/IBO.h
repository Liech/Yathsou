#pragma once

#include <vector>

namespace Ahwassa {
  class IVAO;

  class IBO
  {
  public:
    IBO(const std::vector<int>& content);
    ~IBO();

    unsigned int getID();
    size_t       getSize();
    void         draw(IVAO* vertexBuffer);
    void         drawInstanced(IVAO* vertexBuffer,size_t amount);

  private:
    unsigned int _ibo ;
    size_t       _size;
  };
}
