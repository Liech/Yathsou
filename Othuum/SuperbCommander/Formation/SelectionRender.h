#pragma once

#include "IyathuumCoreLib/BaseTypes/glmAABB.h"
#include "IyathuumCoreLib/BaseTypes/Color.h"

namespace Ahwassa {
  class BasicRectangleRenderer;
}

namespace Superb {
  namespace Formation {
    class SelectionRender {
    public:
      virtual ~SelectionRender() = default;

      void setPosition(const Iyathuum::glmAABB<2> &);
      void draw(Ahwassa::BasicRectangleRenderer&, const Iyathuum::Color&);

    private:
      Iyathuum::glmAABB<2> _position;
    };
  }
}