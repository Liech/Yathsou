#include "SupComVertex.h"

namespace Athanah {
  SupComVertex::SupComVertex() {
    position = glm::vec3(0.0f);
    tangent = glm::vec3(0.0f);
    normal = glm::vec3(0.0f);
    binormal = glm::vec3(0.0f);
    uv1 = glm::vec2(0.0f);
    uv2 = glm::vec2(0.0f);
    for (int i = 0; i < 4; i++)
      bones[i] = 0;
  };

  std::vector<Ahwassa::AttributeDescription> SupComVertex::getBinding() {
    std::vector<Ahwassa::AttributeDescription> result;
    result.push_back(Ahwassa::AttributeDescription("position", 3, Ahwassa::AttributeDescription::DataType::Float));
    result.push_back(Ahwassa::AttributeDescription("tangent", 3, Ahwassa::AttributeDescription::DataType::Float));
    result.push_back(Ahwassa::AttributeDescription("normal", 3, Ahwassa::AttributeDescription::DataType::Float));
    result.push_back(Ahwassa::AttributeDescription("binormal", 3, Ahwassa::AttributeDescription::DataType::Float));
    result.push_back(Ahwassa::AttributeDescription("uv1", 2, Ahwassa::AttributeDescription::DataType::Float));
    result.push_back(Ahwassa::AttributeDescription("uv2", 2, Ahwassa::AttributeDescription::DataType::Float));
    result.push_back(Ahwassa::AttributeDescription("bones", 4, Ahwassa::AttributeDescription::DataType::Char));
    return result;
  }
}