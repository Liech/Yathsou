#pragma once

#include "IyathuumCoreLib/BaseTypes/glmAABB.h"
#include "IyathuumCoreLib/BaseTypes/Color.h"
#include "AhwassaGraphicsLib/InstancedRenderer/IInstancedBox.h"

namespace Ahwassa {
  class InstancedBox : public IInstancedBox {
  public:
    InstancedBox(const glm::mat4&, const Iyathuum::Color&);

    void setMatrix(const glm::mat4&);
    glm::mat4 getMatrix() const;

    void setColor(const Iyathuum::Color&);
    Iyathuum::Color getColor() const final;

    glm::mat4 matrix() const final;
  private:
    glm::mat4       _matrix;
    Iyathuum::Color _color;
  };
}