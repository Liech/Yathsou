#pragma once

#include <memory>
#include "YolonaOss/OpenGL/Updateable.h"

namespace YolonaOss {
  namespace GL {
    class DrawableList;
  }
}

class Fervor : public YolonaOss::GL::Updateable
{
public:
  Fervor();
  virtual void load(YolonaOss::GL::DrawSpecification*) override;
  virtual void update() override;

private:
  std::shared_ptr<YolonaOss::GL::DrawableList>     _preDrawables ;
  std::shared_ptr<YolonaOss::GL::DrawableList>     _postDrawables;
};