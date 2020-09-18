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
  class PhysicEngine;
  class Box;
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
    void drawLandscape();

    std::shared_ptr<Suthanus::PhysicEngine>            _physic;
    std::shared_ptr<Suthanus::Box>                   _landscape;
    std::shared_ptr<YolonaOss::GL::DrawableList>     _preDrawables;
    std::shared_ptr<YolonaOss::GL::DrawableList>     _postDrawables;
    std::shared_ptr<YolonaOss::Camera::CameraSystem> _cam;
    YolonaOss::GL::DrawSpecification*                _spec;
    std::shared_ptr<Protagonist>                     _protagonist;

  };
}