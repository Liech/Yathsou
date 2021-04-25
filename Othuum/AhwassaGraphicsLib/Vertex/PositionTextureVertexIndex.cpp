#include "PositionTextureVertexIndex.h"

#include "IyathuumCoreLib/lib/glm/glm.hpp"
#include <glad/glad.h>
#include <vector>
#include "Core/AttributeDescription.h"

namespace Ahwassa {
  PositionTextureVertexIndex::PositionTextureVertexIndex() : position(0), texture(0) {

  }

  PositionTextureVertexIndex::PositionTextureVertexIndex(glm::vec3 Position, glm::vec2 Texture, float Index) {
    position = Position;
    texture  = Texture ;
    index    = Index   ;
  }

  std::vector<AttributeDescription> PositionTextureVertexIndex::getBinding() {
    std::vector<AttributeDescription> result;
    result.push_back(AttributeDescription("position", 3, AttributeDescription::DataType::Float));
    result.push_back(AttributeDescription("texture" , 2, AttributeDescription::DataType::Float));
    result.push_back(AttributeDescription("index"   , 1, AttributeDescription::DataType::Float));
    return result;
  }

  std::vector<AttributeDescription> PositionTextureVertexIndex::binding() {
    return PositionTextureVertexIndex::getBinding();
  }
}
