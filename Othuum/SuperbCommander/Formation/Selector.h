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
      
      void draw(Ahwassa::BasicRectangleRenderer&);

      bool insideRotate(const glm::vec2&) { return false; }

    private:
      Iyathuum::glmAABB<2> _position;
      Iyathuum::Color      _color;
      bool                 _selected = false;
    };
  }
}