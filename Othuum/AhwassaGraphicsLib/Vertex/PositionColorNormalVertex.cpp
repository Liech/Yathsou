#include "PositionColorNormalVertex.h"

#include "IyathuumCoreLib/lib/glm/glm.hpp"
#include <glad/glad.h>
#include <vector>
#include "AttributeDescription.h"

namespace Ahwassa {
  PositionColorNormalVertex::PositionColorNormalVertex() : position(0),color(0),normal(0){
  
  }

  PositionColorNormalVertex::PositionColorNormalVertex(glm::vec3 Position, glm::vec4 Color, glm::vec3 Normal) {
    position = Position;
    color = Color;
    normal = Normal;
  }

  std::vector<AttributeDescription> PositionColorNormalVertex::getBinding() {
    std::vector<AttributeDescription> result;
    result.push_back(AttributeDescription("position", 3, AttributeDescription::DataType::Float));
    result.push_back(AttributeDescription("color"   , 4, AttributeDescription::DataType::Float));
    result.push_back(AttributeDescription("normal"  , 3, AttributeDescription::DataType::Float));
    return result;
  }
}
