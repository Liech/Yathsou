#pragma once

#include <vector>

namespace Ahwassa {
  class VAO;

  class IBO
  {
  public:
    IBO(const std::vector<int>& content);
    ~IBO();

    unsigned int getID() const;
    size_t       getSize() const;
    void         draw(VAO* vertexBuffer) const;
    void         drawInstanced(VAO* vertexBuffer,size_t amount)const;

  private:
    unsigned int _ibo ;
    size_t       _size;
  };
}
