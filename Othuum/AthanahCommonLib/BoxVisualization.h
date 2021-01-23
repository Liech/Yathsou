#pragma once

#include "YolonaOss/OpenGL/Drawable.h"
#include "IyathuumCoreLib/BaseTypes/Color.h"

namespace Iyathuum {
  struct Color;
}

namespace Suthanus {
  class Box;
}

namespace Athanah {
  class BoxVisualization : public YolonaOss::GL::Drawable {
  public:
    BoxVisualization(std::shared_ptr<Suthanus::Box> target, Iyathuum::Color);
    virtual void load(YolonaOss::GL::DrawSpecification*) override;
    virtual void draw() override;

  private:
    std::shared_ptr<Suthanus::Box> _target;
    Iyathuum::Color                _color ;
  };
}