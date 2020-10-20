#pragma once
#include "YolonaOss/OpenGL/Drawable.h"
#include <set>


namespace Fatboy
{
  class Unit;

  class UnitPool : public YolonaOss::GL::Drawable
  {
  public:
    void addUnit(std::shared_ptr<Unit>);
    void removeUnit(std::shared_ptr<Unit>);
    virtual void load(YolonaOss::GL::DrawSpecification*) override;
    virtual void draw() override;
  private:
    std::set<std::shared_ptr<Unit>> _units;
    YolonaOss::GL::DrawSpecification* _spec;
  };
}