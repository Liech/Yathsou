#pragma once

#include "YolonaOss/OpenGL/Drawable.h"
#include "YolonaOss/OpenGL/Updateable.h"
#include <memory>
namespace YolonaOss
{
  namespace GL
  {
    class DrawableList;
    class DrawSpecification;
  }
  namespace Camera
  {
    class CameraSystem;
  }
}
namespace Suthanus
{
  class PhysicTest;
}

namespace Fatboy
{
  class Protagonist;

  class Fatboy : public YolonaOss::GL::Drawable, public YolonaOss::GL::Updateable
  {
  public:
    Fatboy();

    virtual void load(YolonaOss::GL::DrawSpecification*) override;
    virtual void draw() override;
    virtual void update() override;
  private:
    void initPhysic();

    std::shared_ptr<Suthanus::PhysicTest>            _physic;
    std::shared_ptr<YolonaOss::GL::DrawableList>     _drawables;
    std::shared_ptr<YolonaOss::Camera::CameraSystem> _cam;
    YolonaOss::GL::DrawSpecification*                _spec;
    std::shared_ptr<Protagonist>                     _protagonist;

  };
}