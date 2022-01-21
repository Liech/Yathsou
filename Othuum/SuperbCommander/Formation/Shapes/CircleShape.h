#pragma once

#include "FormationShape.h" 

namespace Superb {
  namespace Formation {
    class CircleShape : public FormationShape {
    public:
      virtual void draw(Ahwassa::BasicRectangleRenderer& renderer) override;
    };
  }
}