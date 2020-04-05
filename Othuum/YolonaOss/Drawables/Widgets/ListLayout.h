#pragma once

#include "Widget.h"
#include <vector>

namespace YolonaOss {
  namespace Widgets {
    class ListLayout : public Widget {
    public:
              ListLayout(BoundingBox2 position);
              int  addWidget(std::shared_ptr<Widget> w);
              void removeWidget(int w);
      virtual void draw() override;
              void setHorizontal(bool horizontal);

    private:
      const float spacing = 0;

      std::vector<std::shared_ptr<Widget>> _widgets;
      bool                                 _horizontal = false;
    };
  }
}