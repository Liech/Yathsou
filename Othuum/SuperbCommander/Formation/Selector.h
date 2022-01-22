#pragma once

#include "IyathuumCoreLib/BaseTypes/glmAABB.h"
#include "IyathuumCoreLib/BaseTypes/Color.h"

namespace Ahwassa {
  class BasicRectangleRenderer;
}

namespace Superb {
  namespace Formation {
    class Selector {
    public:
      virtual ~Selector() = default;

      void setSelected(bool);
      void setColor(const Iyathuum::Color&);
      void setPosition(const Iyathuum::glmAABB<2> &);
      void setRotation(float degree);
      
      void draw(Ahwassa::BasicRectangleRenderer&);

      bool insideRotate(const glm::vec2&);
      bool insideSelect(const glm::vec2&);

    private:
      glm::vec2 rot(const glm::vec2&);
      void updateMatrix();

      glm::vec2 rotatorPosition();

      float                _rotation = 0;
      glm::mat4            _matrix;
      Iyathuum::glmAABB<2> _position;
      Iyathuum::Color      _color;
      bool                 _selected = false;
    };
  }
}