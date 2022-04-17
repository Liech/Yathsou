#include "PositionTextureVertex.h"

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <vector>
#include "AhwassaGraphicsLib/Core/AttributeDescription.h"

namespace Ahwassa {
  PositionTextureVertex::PositionTextureVertex() : position(0), texture(0) {

  }

  PositionTextureVertex::PositionTextureVertex(glm::vec3 Position, glm::vec2 Texture) {
    position = Position;
    texture  = Texture ;
  }

  std::vector<AttributeDescription> PositionTextureVertex::getBinding() {
    std::vector<AttributeDescription> result;
    result.push_back(AttributeDescription("position", 3, AttributeDescription::DataType::Float));
    result.push_back(AttributeDescription("texture" , 2, AttributeDescription::DataType::Float));
    return result;
  }

  std::vector<AttributeDescription> PositionTextureVertex::binding() {
    return PositionTextureVertex::getBinding();
  }
}
