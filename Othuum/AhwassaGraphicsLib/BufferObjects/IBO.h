#pragma once

#include <vector>

namespace Ahwassa {
  class VAO;

  class IBO
  {
  public:
    IBO(const std::vector<int>& content);
    ~IBO();

    unsigned int getID();
    size_t       getSize();
    void         draw(VAO* vertexBuffer);
    void         drawInstanced(VAO* vertexBuffer,size_t amount);

  private:
    unsigned int _ibo ;
    size_t       _size;
  };
}
