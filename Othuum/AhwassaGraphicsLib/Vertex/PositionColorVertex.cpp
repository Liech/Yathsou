#include "PositionColorVertex.h"

#include "IyathuumCoreLib/lib/glm/glm.hpp"
#include <glad/glad.h>
#include <vector>
#include "AttributeDescription.h"

namespace Ahwassa {
  PositionColorVertex::PositionColorVertex() : position(0), color(0) {

  }

  PositionColorVertex::PositionColorVertex(glm::vec3 Position, glm::vec4 Color) {
    position = Position;
    color = Color;
  }

  std::vector<AttributeDescription> PositionColorVertex::getBinding() {
    std::vector<AttributeDescription> result;
    result.push_back(AttributeDescription("position", 3, AttributeDescription::DataType::Float));
    result.push_back(AttributeDescription("color", 4, AttributeDescription::DataType::Float));
    return result;
  }
}
