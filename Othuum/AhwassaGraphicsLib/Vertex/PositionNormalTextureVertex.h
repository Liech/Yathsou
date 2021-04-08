#pragma once

#include "IVertex.h"
#include "IyathuumCoreLib/lib/glm/glm.hpp"
#include <vector>

namespace Ahwassa {
  struct AttributeDescription;

  struct PositionNormalTextureVertex : public IVertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texture;

    PositionNormalTextureVertex();
    PositionNormalTextureVertex(glm::vec3 Position, glm::vec3 normal, glm::vec2 texture);

    static std::vector<AttributeDescription> getBinding();
    virtual std::vector<AttributeDescription> binding() override;
  };
}