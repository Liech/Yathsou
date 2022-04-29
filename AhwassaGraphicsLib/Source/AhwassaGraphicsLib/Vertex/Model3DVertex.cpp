#include "Model3DVertex.h"

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <vector>
#include "AhwassaGraphicsLib/Core/AttributeDescription.h"

namespace Ahwassa {
  Model3DVertex::Model3DVertex() :
    position  (0),
    normal    (0),
    bitangent (0),
    tangent   (0),
    texCoord (0),
    boneWeight(0),
    boneIndex(0)
  {
  }

  Model3DVertex::Model3DVertex(glm::vec3 Position, glm::vec3 Normal, glm::vec3 Bitangent, glm::vec3 Tangent, glm::vec2 Texcoord, glm::vec4 boneI, glm::vec4 boneW){
    position   = Position;
    normal     = Normal;
    bitangent  = Bitangent;
    tangent    = Tangent;
    texCoord   = Texcoord;
    boneWeight = boneW;
    boneIndex  = boneIndex;
  }

  std::vector<AttributeDescription> Model3DVertex::getBinding() {
    std::vector<AttributeDescription> result;
    result.push_back(AttributeDescription("position"  , 3, AttributeDescription::DataType::Float));
    result.push_back(AttributeDescription("normal"    , 3, AttributeDescription::DataType::Float));
    result.push_back(AttributeDescription("bitangent" , 3, AttributeDescription::DataType::Float));
    result.push_back(AttributeDescription("tangent"   , 3, AttributeDescription::DataType::Float));
    result.push_back(AttributeDescription("texCoord"  , 2, AttributeDescription::DataType::Float));
    result.push_back(AttributeDescription("boneIndex" , 4, AttributeDescription::DataType::Float));
    result.push_back(AttributeDescription("boneWeight", 4, AttributeDescription::DataType::Float));
    return result;
  }

  std::vector<AttributeDescription> Model3DVertex::binding() const {
    return Model3DVertex::getBinding();
  }

}
