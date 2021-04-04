#pragma once

#include "IyathuumCoreLib/lib/glm/glm.hpp"
namespace Ahwassa {
  class IInstancedBox {
  public:
    virtual glm::mat4 matrix() const = 0;
    virtual Iyathuum::Color getColor() const = 0;
  };
}