#pragma once

#include "FormationShape.h" 

namespace Superb {
  namespace Formation {
    class TriangleShape : public FormationShape {
    public:
      virtual void draw(Ahwassa::BasicRectangleRenderer& renderer) override;
    };
  }
}