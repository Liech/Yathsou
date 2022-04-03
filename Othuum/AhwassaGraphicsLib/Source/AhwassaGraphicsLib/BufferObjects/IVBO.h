#pragma once

#include <vector>

namespace Ahwassa {
  struct AttributeDescription;

  class IVBO {
  public:
    IVBO(size_t size, size_t structsize, const void* pos);
    virtual ~IVBO();

    unsigned int getID();
    size_t       getSize();
    virtual std::vector<AttributeDescription> getBinding() = 0;
  protected:
    void setRawData(const void* pos, size_t size);
  private:
    unsigned int _id = 0;
    size_t _size;
    size_t _structsize;
  };
  }