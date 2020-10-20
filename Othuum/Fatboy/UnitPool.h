#pragma once
#include "YolonaOss/OpenGL/Drawable.h"
#include <set>
#include <map>

namespace Suthanus
{
  class PhysicObject;
}

namespace Fatboy
{
  class Unit;

  class UnitPool : public YolonaOss::GL::Drawable
  {
  public:
    void  addUnit(std::shared_ptr<Unit>);
    void  removeUnit(std::shared_ptr<Unit>);
    std::shared_ptr<Unit> physicBodyToUnit(std::shared_ptr<Suthanus::PhysicObject>);
    virtual void load(YolonaOss::GL::DrawSpecification*) override;
    virtual void draw() override;
  private:
    std::set<std::shared_ptr<Unit>> _units;
    std::map<std::shared_ptr<Suthanus::PhysicObject>, std::weak_ptr<Unit>> _physicMap;
    YolonaOss::GL::DrawSpecification* _spec;
  };
}