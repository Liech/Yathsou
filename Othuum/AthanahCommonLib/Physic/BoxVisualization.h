#pragma once

#include <memory>

#include "AhwassaGraphicsLib/Drawables/Drawable.h"
#include "IyathuumCoreLib/BaseTypes/Color.h"

namespace Iyathuum {
  struct Color;
}
namespace Ahwassa {
  class BasicBoxRenderer;
  class Window;
}
namespace Suthanus {
  class Box;
}

namespace Athanah {
  class BoxVisualization : public Ahwassa::Drawable {
  public:
    BoxVisualization(std::shared_ptr<Suthanus::Box> target, Iyathuum::Color, Ahwassa::Window*);
    virtual void draw() override;

  private:
    std::shared_ptr<Ahwassa::BasicBoxRenderer> _box;
    std::shared_ptr<Suthanus::Box> _target;
    Iyathuum::Color                _color ;
  };
}