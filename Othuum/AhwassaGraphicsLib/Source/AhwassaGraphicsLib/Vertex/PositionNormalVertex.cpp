#include "PositionNormalVertex.h"

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <vector>
#include "AhwassaGraphicsLib/Core/AttributeDescription.h"

namespace Ahwassa {
  PositionNormalVertex::PositionNormalVertex() : position(0), normal(0) {

  }

  PositionNormalVertex::PositionNormalVertex(glm::vec3 Position, glm::vec3 Normal) {
    position = Position;
    normal   = Normal;
  }

  std::vector<AttributeDescription> PositionNormalVertex::getBinding() {
    std::vector<AttributeDescription> result;
    result.push_back(AttributeDescription("position", 3, AttributeDescription::DataType::Float));
    result.push_back(AttributeDescription("normal"  , 3, AttributeDescription::DataType::Float));
    return result;
  }

  std::vector<AttributeDescription> PositionNormalVertex::binding() {
    return PositionNormalVertex::getBinding();
  }
}
