#pragma once

#include "Widget.h"
#include <vector>
#include <functional>

namespace YolonaOss {
  namespace Widgets {
    class Button;
    class Label;

    class ListLayout : public Widget {
    public:
              ListLayout(Iyathuum::AABB<2> position);

              int                                  addWidget(std::shared_ptr<Widget> w);
              std::shared_ptr<Widgets::Button>     addButton(std::string name, std::function<void()> onClicked, Iyathuum::AABB<2> size = Iyathuum::AABB<2>({ 0.0, 0.0 }, { 200.0, 50.0 }));
              std::shared_ptr<Widgets::ListLayout> addLayout();
              std::shared_ptr<Widgets::Label>      addLabel(std::string text);

              void removeWidget(int w);
      virtual void draw() override;
              void setHorizontal(bool horizontal);
      virtual void setVisible(bool visible) override;

      std::vector<std::shared_ptr<Widget>> getWidgets();

    private:
      const float spacing = 0;

      std::vector<std::shared_ptr<Widget>> _widgets;
      bool                                 _horizontal = false;
    };
  }
}