#include "Core/AttributeDescription.h"

#include <stdexcept>
namespace Ahwassa {
  AttributeDescription::AttributeDescription(const std::string& _name, const int& _size, const DataType& _type, bool _instancing) {
    name       = _name;
    size       = _size;
    type       = _type;
    instancing = _instancing;
  }

  std::string AttributeDescription::getName() const {
    return name;
  }

  AttributeDescription::DataType AttributeDescription::getType() const {
    return type;
  }

  size_t AttributeDescription::getSize() const {
    switch (type)
    {
    case AttributeDescription::DataType::Float:
      return sizeof(float) * size;
      break;
    case AttributeDescription::DataType::Char:
      return sizeof(unsigned char) * size;
      break;
    case AttributeDescription::DataType::UInt:
      return sizeof(unsigned int) * size;
      break;
    default:
      break;
    }
    throw std::runtime_error("Unkown DataType");
  }

  size_t AttributeDescription::getSizeOf() const {
    return size;
  }

  bool AttributeDescription::isInstancing() const {
    return instancing;
  }

  std::string AttributeDescription::getTypeAsString() const{
    switch (type)
    {
    case AttributeDescription::DataType::Float:
      if (size == 1) return "float";
      else if (size == 2) return "vec2";
      else if (size == 3) return "vec3";
      else if (size == 4) return "vec4";
      break;
    case AttributeDescription::DataType::Char:
      return "uint";
    case AttributeDescription::DataType::UInt:
      return "uint";
    default:
      break;
    }
    throw std::runtime_error("unkown type");
  }
}