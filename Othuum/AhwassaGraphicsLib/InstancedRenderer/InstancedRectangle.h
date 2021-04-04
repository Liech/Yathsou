#pragma once

#include "IyathuumCoreLib/BaseTypes/glmAABB.h"
#include "IyathuumCoreLib/BaseTypes/Color.h"
#include "AhwassaGraphicsLib/Drawables/Drawable.h"

namespace Ahwassa {
  class InstancedRectangle{
  public:
    Iyathuum::glmAABB<2> location;
    Iyathuum::Color      color   ;

    glm::mat4 matrix() const;
    glm::vec3 colorVec() const;
  };
}