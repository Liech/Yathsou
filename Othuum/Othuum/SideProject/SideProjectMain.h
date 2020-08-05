#pragma once

#include <vector>

#include "YolonaOss/OpenGL/Drawable.h"
#include "SuthanusPhysicsLib/Box.h"
#include "SuthanusPhysicsLib/Sphere.h"
#include "SuthanusPhysicsLib/Vehicle.h"

namespace YolonaOss{namespace GL{class DrawableList;}}
namespace Suthanus { class PhysicTest; }

namespace SideProject
{
  class SideProjectMain : public YolonaOss::GL::Drawable
  {
  public:
    virtual void load(YolonaOss::GL::DrawSpecification*) override;
    virtual void draw()                                  override;
  private:
    std::shared_ptr<YolonaOss::GL::DrawableList>      _list;
    std::shared_ptr< Suthanus::PhysicTest>            _phys;
    std::vector< std::shared_ptr< Suthanus::Box> >    _boxes;
    std::vector< std::shared_ptr< Suthanus::Sphere> > _spheres;
                 std::shared_ptr< Suthanus::Vehicle > _vehicle;
  };
}