#pragma once

#include "glm/glm.hpp"
#include <glad/glad.h>
#include <vector>
#include "AttributeDescription.h"
namespace YolonaOss {
  namespace GL {
    struct PositionNormalVertex {
      glm::vec3 position;
      glm::vec3 normal;
      PositionNormalVertex() :position(0.0f), normal(0.0f) {};
      PositionNormalVertex(glm::vec3 Position, glm::vec3 Normal) {
        position = Position;
        normal = Normal;
      }

      std::vector<AttributeDescription> getBinding() {
        std::vector<AttributeDescription> result;
        result.push_back(AttributeDescription("position", 3, AttributeDescription::DataType::Float));
        result.push_back(AttributeDescription("normal", 3, AttributeDescription::DataType::Float));
        return result;
      }
    };
  }
}