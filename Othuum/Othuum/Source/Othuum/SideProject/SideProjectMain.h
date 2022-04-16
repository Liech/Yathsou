#pragma once

#include <vector>
#include <memory>

#include "AhwassaGraphicsLib/Drawables/Drawable.h"

namespace Suthanus { class PhysicEngine; }

namespace SideProject
{
  class SideProjectMain : public Ahwassa::Drawable
  {
  public:
    SideProjectMain(Ahwassa::Window*);
    virtual void draw()                                  override;
    void load();
  private:
    std::vector<std::shared_ptr<Ahwassa::Drawable>> _list;
  };
}