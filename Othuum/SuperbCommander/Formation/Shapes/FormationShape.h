#pragma once

#include "IyathuumCoreLib/lib/glm/glm.hpp"
#include "IyathuumCoreLib/BaseTypes/glmAABB.h"

namespace Ahwassa {
  class BasicRectangleRenderer;
}

namespace Superb {
  namespace Formation {
    class FormationShape {
    public:
      const Iyathuum::glmAABB<2>& getPosition() const;
      void                        setPosition(const Iyathuum::glmAABB<2>&);
      float                       getRotation() const;
      void                        setRotation(float degree);
      virtual void                draw(Ahwassa::BasicRectangleRenderer& renderer) {};

    private:
      Iyathuum::glmAABB<2> _position;
      float                _rotation = 0;
    };
  }
}