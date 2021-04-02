#pragma once

#include "Drawable.h"
#include "IyathuumCoreLib/BaseTypes/Color.h"

namespace Ahwassa {
  class Window;

  class Background : public Drawable
  {
  public:
    Background(Window*);
    ~Background();

    virtual void draw() override;

    void setColor(const Iyathuum::Color&);
    Iyathuum::Color getColor() const;

  private:
    Iyathuum::Color _color;
  };
}