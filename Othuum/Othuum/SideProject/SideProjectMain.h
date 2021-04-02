#pragma once

#include <vector>
#include <memory>

#include "YolonaOss/OpenGL/DrawableList.h"
#include "YolonaOss/OpenGL/Drawable.h"

namespace Suthanus { class PhysicEngine; }

namespace SideProject
{
  class SideProjectMain : public YolonaOss::GL::Drawable
  {
  public:
    virtual void load(YolonaOss::GL::DrawSpecification*) override;
    virtual void draw()                                  override;
  private:
    std::shared_ptr<YolonaOss::GL::DrawableList>      _list;
  };
}