#pragma once

#include <glad/glad.h>
#include <vector>
#include "AttributeDescription.h"
namespace YolonaOss {
  namespace GL {
    struct PositionVertex {
      glm::vec3 pos;
      PositionVertex() { pos = glm::vec3(0, 0, 0); };
      PositionVertex(glm::vec3 v) {
        pos = v;
      }

      static std::vector<AttributeDescription> getBinding() {
        std::vector<AttributeDescription> result;
        result.push_back(AttributeDescription("position", 3, AttributeDescription::DataType::Float));
        return result;
      }
    };
  }
}