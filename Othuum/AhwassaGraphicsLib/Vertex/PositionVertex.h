#pragma once

#include "IVertex.h"
#include "IyathuumCoreLib/lib/glm/glm.hpp"
#include <vector>

namespace Ahwassa {
  struct AttributeDescription;

  struct PositionVertex : public IVertex {
    glm::vec3 position;

    PositionVertex();
    PositionVertex(glm::vec3 Position);

    static std::vector<AttributeDescription> getBinding();
    virtual std::vector<AttributeDescription> binding() override;
  };
}