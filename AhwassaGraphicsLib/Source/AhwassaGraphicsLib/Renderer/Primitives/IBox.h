#pragma once

#include <glm/glm.hpp>
namespace Ahwassa {
  class IBox {
  public:
    virtual glm::mat4 matrix() const = 0;
    virtual Iyathuum::Color getColor() const = 0;
  };
}