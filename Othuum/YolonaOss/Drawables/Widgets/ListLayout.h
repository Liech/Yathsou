#pragma once

#include "Widget.h"
#include <vector>
#include <functional>

namespace YolonaOss {
  namespace Widgets {
    class Button;
    class Label;
    class LineEdit;

    class ListLayout : public Widget {
    public:
              ListLayout(Iyathuum::AABB<2> position, Widget* parent = nullptr);

              int                                  addWidget(std::shared_ptr<Widget> w);
              std::shared_ptr<Widgets::Button>     addButton(std::string name, std::function<void()> onClicked, Iyathuum::AABB<2> size = Iyathuum::AABB<2>({ 0.0, 0.0 }, { 200.0, 50.0 }));
              std::shared_ptr<Widgets::ListLayout> addLayout();
              std::shared_ptr<Widgets::Label>      addLabel(std::string text);
              std::shared_ptr<Widgets::LineEdit>   addLineEdit(std::string text);

              void removeWidget(int w);
      virtual void draw() override;
              void setHorizontal(bool horizontal);
      virtual void setVisible(bool visible)        override;
      virtual void adjustSize()                    override;

      void setMaximumSize(glm::vec2 size) { _maximumSize = size; }

      std::vector<std::shared_ptr<Widget>> getWidgets();

    private:
      const float spacing = 0;

      Iyathuum::AABB<2> getElementSize();

      std::vector<std::shared_ptr<Widget>> _widgets;
      bool                                 _horizontal = false;
      glm::vec2                            _maximumSize = glm::vec2(0,0);
    };
  }
}