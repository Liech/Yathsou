#pragma once

#include <vector>
#include "AhwassaGraphicsLib/Core/AttributeDescription.h"
#include <IyathuumCoreLib/lib/glm/glm.hpp>

namespace Athanah {
  struct SupComVertex {
    glm::vec3 position;
    glm::vec3 tangent ;
    glm::vec3 normal  ;
    glm::vec3 binormal;
    glm::vec2 uv1     ;
    glm::vec2 uv2     ;
    unsigned char bones[4];

    SupComVertex();

    static std::vector<Ahwassa::AttributeDescription> getBinding();
  };
}