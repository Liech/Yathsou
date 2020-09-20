#pragma once

#include "Drawable.h"
#include <vector>
#include <memory>
namespace YolonaOss {
  namespace GL {
    class DrawableList : public Drawable
    {
    public:
      DrawableList() {}
      virtual ~DrawableList()override {}

      void addDrawable(std::shared_ptr<Drawable> draw);
      virtual void load(DrawSpecification*) override;
      virtual void draw() override;
      virtual void debugDraw() override;


    private:
      std::vector<std::shared_ptr<Drawable>> _drawables;
    };
  }
}