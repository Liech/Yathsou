#pragma once

#include "IyathuumCoreLib/BaseTypes/glmAABB.h"
#include "IyathuumCoreLib/BaseTypes/Color.h"

namespace Ahwassa {
  class Rectangle{
  public:
    Iyathuum::glmAABB<2> location;
    Iyathuum::Color      color   ;

    glm::mat4 matrix() const;
    glm::vec3 colorVec() const;
  };
}