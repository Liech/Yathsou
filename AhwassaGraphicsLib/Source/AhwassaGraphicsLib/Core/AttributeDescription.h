#pragma once

#include <string>
#include <stdexcept>
#include <nlohmann/json.hpp>

namespace Ahwassa {
  struct AttributeDescription {
    enum class DataType {
      Float = 0x1406 , //glad.h->GL_FLOAT 0x1406
      Char  = 0x1400 , //glad.h->GL_BYTE 0x1400
      UInt  = 0x1405 ,//GL_UNSIGNED_INT 0x1405
    };

    AttributeDescription(const std::string& _name, const int& _size, const DataType& _type, bool instancing = false);
    AttributeDescription(const nlohmann::json&);

    size_t                         getSize()         const;
    size_t                         getSizeOf()       const;
    std::string                    getTypeAsString() const;
    std::string                    getName()         const;
    AttributeDescription::DataType getType()         const;
    bool                           isInstancing()    const;

    nlohmann::json toJson() const;

  private:
    std::string name              ;
    int         size              ;
    DataType    type              ;
    bool        instancing = false;
  };
}