#include "AttributeDescription.h"

#include <stdexcept>
namespace Ahwassa {
  AttributeDescription::AttributeDescription(const std::string& _name, const int& _size, const DataType& _type) {
    name = _name;
    size = _size;
    type = _type;
  }

  std::string AttributeDescription::getName() const {
    return name;
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
    default:
      break;
    }
    throw std::runtime_error("Unkown DataType");
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
    default:
      break;
    }
    throw std::runtime_error("unkown type");
  }
}