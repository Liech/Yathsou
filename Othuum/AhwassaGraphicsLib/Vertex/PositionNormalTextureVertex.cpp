#include "PositionNormalTextureVertex.h"

#include "IyathuumCoreLib/lib/glm/glm.hpp"
#include <glad/glad.h>
#include <vector>
#include "AttributeDescription.h"

namespace Ahwassa {
  PositionNormalTextureVertex::PositionNormalTextureVertex() : position(0), normal(0), texture(0) {

  }

  PositionNormalTextureVertex::PositionNormalTextureVertex(glm::vec3 Position, glm::vec3 Normal, glm::vec2 Texture) {
    position = Position;
    normal   = Normal;
    texture  = Texture;
  }

  std::vector<AttributeDescription> PositionNormalTextureVertex::getBinding() {
    std::vector<AttributeDescription> result;
    result.push_back(AttributeDescription("position", 3, AttributeDescription::DataType::Float));
    result.push_back(AttributeDescription("normal"  , 3, AttributeDescription::DataType::Float));
    result.push_back(AttributeDescription("texture" , 2, AttributeDescription::DataType::Float));
    return result;
  }
}
