#pragma once

#include "FormationShape.h" 

namespace Superb {
  namespace Formation {
    class RectangleShape : public FormationShape {
    public:
      virtual void draw(Ahwassa::BasicRectangleRenderer& renderer) override;
    };
  }
}