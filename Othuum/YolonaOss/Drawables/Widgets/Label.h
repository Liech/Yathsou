#pragma once

#include "Widget.h"
#include <string>

namespace YolonaOss {
  namespace Widgets {
    class Label : public Widget
    {
    public:
      Label();
      Label(std::string name, Iyathuum::AABB<2> position, Widget* parent = nullptr);
      ~Label();

      // Inherited via Drawable
      virtual void load(GL::DrawSpecification*) override;
      virtual void draw() override;


    private:
      std::string               _name;
    };
  }
}