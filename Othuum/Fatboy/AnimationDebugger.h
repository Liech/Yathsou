#pragma once

#include <memory>
#include <string>

#include "YolonaOss/OpenGL/Drawable.h"
#include "YolonaOss/OpenGL/Updateable.h"

namespace YolonaOss
{
  namespace Widgets {
    class ListLayout;
  }
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
class SupComModel;
namespace Haas
{
  class ScriptEngine;
}
namespace Fatboy{
  class AnimationDebugger : public YolonaOss::GL::Drawable, public YolonaOss::GL::Updateable {
  public:
    AnimationDebugger();

    virtual void load(YolonaOss::GL::DrawSpecification*) override;
    virtual void draw() override;
    virtual void update() override;

  private:
    void loadMenu();
    void loadModel();
    void loadScript();

    void drawModel();

    std::shared_ptr<YolonaOss::GL::DrawableList>     _preDrawables;
    std::shared_ptr<YolonaOss::GL::DrawableList>     _postDrawables;
    std::shared_ptr<YolonaOss::Camera::CameraSystem> _cam;
    YolonaOss::GL::DrawSpecification*                _spec;
    
    std::shared_ptr<YolonaOss::Widgets::ListLayout>  _layout;

    std::shared_ptr< SupComModel> _modl;
    YolonaOss::SupComGLMesh* _scMesh;
    std::shared_ptr<Haas::ScriptEngine> _script;
    
    std::string _animName = "walk01";
    std::string _unitName = "URL0106";

    bool _keyPressed = false;
  };
}