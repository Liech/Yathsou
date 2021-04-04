#pragma once

#include "IyathuumCoreLib/BaseTypes/glmAABB.h"
#include "IyathuumCoreLib/BaseTypes/Color.h"
#include "AhwassaGraphicsLib/InstancedRenderer/IInstancedBox.h"

namespace Ahwassa {
  class InstancedDot : public IInstancedBox {
  public:
    InstancedDot(const glm::vec3& pos, const float& size, const Iyathuum::Color& clr);

    void setPosition(const glm::vec3& pos);
    glm::vec3 getPosition() const;

    void setSize(const float& size);
    float getSize() const;

    void setColor(const Iyathuum::Color&);
    Iyathuum::Color getColor() const final;

    glm::mat4 matrix() const final;
  private:
    void recalculate();

    glm::vec3       _position;
    float           _size;
    Iyathuum::Color _color;
    glm::mat4       _matrix;
  };
}