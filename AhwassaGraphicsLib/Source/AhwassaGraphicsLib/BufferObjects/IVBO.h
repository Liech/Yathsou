#pragma once

#include <vector>

namespace Ahwassa {
  struct AttributeDescription;

  class IVBO {
  public:
    IVBO(size_t size, size_t structsize, const void* pos);
    virtual ~IVBO();

    unsigned int getID()   const;
    size_t       getSize() const;
    virtual std::vector<AttributeDescription> getBinding() const = 0;
  protected:
    void setRawData(const void* pos, size_t size);
  private:
    unsigned int _id = 0;
    size_t _size;
    size_t _structsize;
  };
  }