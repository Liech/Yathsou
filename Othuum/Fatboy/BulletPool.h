#pragma once
#include "YolonaOss/OpenGL/Drawable.h"
#include <set>

namespace Suthanus
{
  class Sphere;
}

namespace Fatboy
{
  class BulletPool : public YolonaOss::GL::Drawable
  {
  public:
    void addBullet(std::shared_ptr<Suthanus::Sphere>);
    virtual void load(YolonaOss::GL::DrawSpecification*) override;
    virtual void draw() override;
  private:
    std::set<std::shared_ptr<Suthanus::Sphere>> _bullets;
    YolonaOss::GL::DrawSpecification*                 _spec;
  };
}