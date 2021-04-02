#pragma once
#include "glad/glad.h"
#include <vector>
#include <stdexcept>
namespace Ahwassa {
  class IVBO {
  public:
    IVBO(size_t size, size_t structsize,const void* pos);
    virtual ~IVBO();

    unsigned int getID()  ;
    size_t       getSize();
  protected:
    void setData(const void* pos, size_t size);
  private:
    unsigned int _id;
    size_t _size;
    size_t _structsize;
  };

  template<typename Struct>
  class VBO : IVBO
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
      setData(content.data(), content.size());
    }
  };
}
