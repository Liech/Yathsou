#pragma once

#include <string>
#include <stdexcept>

namespace Ahwassa {
  struct AttributeDescription {
    enum class DataType {
      Float = 0x1406 , //glad.h->GL_FLOAT 0x1406
      Char  = 0x1400 , //glad.h->GL_BYTE 0x1400
    };

    AttributeDescription(const std::string& _name, const int& _size, const DataType& _type);

    size_t                         getSize()         const;
    size_t                         getSizeOf()       const;
    std::string                    getTypeAsString() const;
    std::string                    getName()         const;
    AttributeDescription::DataType getType()         const;

  private:
    std::string name;
    int         size;
    DataType    type;
  };
}