#pragma once

#include <memory>

#include "YolonaOss/OpenGL/Drawable.h"
#include "YolonaOss/OpenGL/Updateable.h"

namespace YolonaOss
{
  namespace GL
  {
    class DrawableList;
    class DrawSpecification;
  }
  class Mesh;
  class SupComGLMesh;
  namespace Camera
  {
    class CameraSystem;
  }
}

namespace Fatboy{
  class AnimationDebugger : public YolonaOss::GL::Drawable, public YolonaOss::GL::Updateable {
  public:
    AnimationDebugger();

    virtual void load(YolonaOss::GL::DrawSpecification*) override;
    virtual void draw() override;
    virtual void update() override;

  private:

    std::shared_ptr<YolonaOss::GL::DrawableList>     _preDrawables;
    std::shared_ptr<YolonaOss::GL::DrawableList>     _postDrawables;
    std::shared_ptr<YolonaOss::Camera::CameraSystem> _cam;
    YolonaOss::GL::DrawSpecification*                _spec;


    bool _keyPressed = false;
  };
}