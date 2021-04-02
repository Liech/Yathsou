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
    void         bind(IVAO* vertexBuffer);

  private:
    unsigned int _ibo ;
    size_t       _size;
  };
}
