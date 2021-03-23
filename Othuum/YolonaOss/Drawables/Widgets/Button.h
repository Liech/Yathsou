#pragma once

#include "Widget.h"
#include <string>
#include <functional>

namespace YolonaOss {
  namespace Widgets {
    class Button : public Widget
    {
    public:
      Button();
      Button(std::string name, Iyathuum::AABB<2> position, std::function<void(void)> clickedFunction, Widget* parent = nullptr);
      ~Button();

      // Inherited via Drawable
      virtual void load(GL::DrawSpecification*) override;
      virtual void draw() override;

      virtual void mouseEnter() override;
      virtual void mouseLeave() override;
      virtual bool mouseClick(glm::vec2 position, Iyathuum::Key k) override;
      virtual void setVisible(bool visible) override;

      void setText(std::string t);


    private:
      std::string               _name;
      std::function<void(void)> _clickedFunction;

      bool _hovered = false;
    };
  }
}