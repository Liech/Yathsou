#pragma once

#include <vector>
#include <IyathuumCoreLib/lib/glm/glm.hpp>

namespace Ahwassa {
  struct AttributeDescription;

  struct SupComVertex {     
    glm::vec3 position;
    glm::vec3 tangent ;
    glm::vec3 normal  ;
    glm::vec3 binormal;
    glm::vec2 uv1     ;
    glm::vec2 uv2     ;
    unsigned char bones[4];

    SupComVertex();

    static std::vector<AttributeDescription> getBinding();
  };
}