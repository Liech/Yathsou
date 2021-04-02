#pragma once

namespace Ahwassa {
  class IVBO {
  public:
    IVBO(size_t size, size_t structsize, const void* pos);
    virtual ~IVBO();

    unsigned int getID();
    size_t       getSize();
  protected:
    void setData(const void* pos, size_t size);
  private:
    unsigned int _id;
    size_t _size;
    size_t _structsize;
  };
  }