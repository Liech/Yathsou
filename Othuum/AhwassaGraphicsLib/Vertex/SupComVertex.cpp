#include "SupComVertex.h"

#include <vector>
#include <glad/glad.h>

#include "IyathuumCoreLib/lib/glm/glm.hpp"
#include "AttributeDescription.h"

namespace Ahwassa {
  SupComVertex::SupComVertex() {
    position = glm::vec3(0.0f);
    tangent  = glm::vec3(0.0f);
    normal   = glm::vec3(0.0f);
    binormal = glm::vec3(0.0f);
    uv1 = glm::vec2(0.0f);
    uv2 = glm::vec2(0.0f);
    for (int i = 0; i < 4; i++)
      bones[i] = 0;
  };

  std::vector<AttributeDescription> SupComVertex::getBinding() {
    std::vector<AttributeDescription> result;
    result.push_back(AttributeDescription("position", 3, AttributeDescription::DataType::Float));
    result.push_back(AttributeDescription("tangent", 3, AttributeDescription::DataType::Float));
    result.push_back(AttributeDescription("normal", 3, AttributeDescription::DataType::Float));
    result.push_back(AttributeDescription("binormal", 3, AttributeDescription::DataType::Float));
    result.push_back(AttributeDescription("uv1", 2, AttributeDescription::DataType::Float));
    result.push_back(AttributeDescription("uv2", 2, AttributeDescription::DataType::Float));
    result.push_back(AttributeDescription("bones", 4, AttributeDescription::DataType::Char));
    return result;
  }
}
