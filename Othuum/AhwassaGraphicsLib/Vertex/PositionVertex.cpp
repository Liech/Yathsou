#include "PositionVertex.h"

#include "IyathuumCoreLib/lib/glm/glm.hpp"
#include <glad/glad.h>
#include <vector>
#include "Core/AttributeDescription.h"

namespace Ahwassa {
  PositionVertex::PositionVertex() : position(0) {

  }

  PositionVertex::PositionVertex(glm::vec3 Position) {
    position = Position;
  }

  std::vector<AttributeDescription> PositionVertex::getBinding() {
    std::vector<AttributeDescription> result;
    result.push_back(AttributeDescription("position", 3, AttributeDescription::DataType::Float));
    return result;
  }
}
