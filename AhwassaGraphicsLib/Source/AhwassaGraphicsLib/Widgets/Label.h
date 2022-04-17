#pragma once

#include <string>

#include "AhwassaGraphicsLib/Input/UIElement.h"
#include "AhwassaGraphicsLib/Drawables/Drawable.h"

namespace Ahwassa {
  class Label : public UIElement, public Drawable
  {
  public:
    Label(Window* w);
    Label(std::string name, Iyathuum::glmAABB<2> position, Window* w, UIElement* parent = nullptr);
    ~Label();

    virtual void draw() override;

    void setText(std::string text) { _name = text; }
  private:
    std::string               _name;
  };
}