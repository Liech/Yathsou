#pragma once

#include "IyathuumCoreLib/BaseTypes/glmAABB.h"
#include "IyathuumCoreLib/BaseTypes/Color.h"
#include "AhwassaGraphicsLib/Renderer/IBox.h"

namespace Ahwassa {
  class Line : public IBox {
  public:
    Line(const glm::vec3& start, const glm::vec3& end, const float& size, const Iyathuum::Color&);

    void setStart(const glm::vec3& pos);
    glm::vec3 getStart() const;

    void setEnd(const glm::vec3& pos);
    glm::vec3 getEnd() const;

    void setThickness(const float& size);
    float getThickness() const;

    void setColor(const Iyathuum::Color&);
    Iyathuum::Color getColor() const final;

    glm::mat4 matrix() const final;
  private:
    void recalculate();

    glm::vec3       _start ;
    glm::vec3       _end   ;
    float           _size  ;
    Iyathuum::Color _clr   ;
    glm::mat4       _matrix;    
  };
}