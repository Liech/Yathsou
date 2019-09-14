#pragma once

#include <glad/glad.h>
#include <string>

struct AttributeDescription {
  enum class DataType {
    Float = GL_FLOAT
  };

  AttributeDescription(std::string _name, int _size, DataType _type) {
    name = _name;
    size = _size;
    type = _type;
  }
  size_t getSize() {
    switch (type)
    {
    case AttributeDescription::DataType::Float:
      return sizeof(float) * size;
      break;
    default:
      break;
    }
  }

  std::string getTypeAsString() {
    switch (type)
    {
    case AttributeDescription::DataType::Float:
      if (size == 1) return "float";
      else if (size == 2) return "vec2";
      else if (size == 3) return "vec3";
      else if (size == 4) return "vec4";
      break;
    default:
      break;
    }
    throw std::runtime_error("unkown type");
  }

  std::string name;
  int size;
  DataType type;
};
