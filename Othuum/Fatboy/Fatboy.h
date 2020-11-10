#pragma once

#include "YolonaOss/OpenGL/Drawable.h"
#include "YolonaOss/OpenGL/Updateable.h"
#include "IyathuumCoreLib/BaseTypes/MultiDimensionalArray.h"
#include "IyathuumCoreLib/BaseTypes/Color.h"
#include <memory>
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
namespace Suthanus
{
  class PhysicEngine;
  class Box;
  class PhysicObject;
  class HeightMap;
}
namespace Haas
{
  class ScriptEngine;
}
class SupComModel;
namespace Fatboy
{
  class Protagonist;
  class ScriptAPI;
  class Context;
 
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
    void initEnemys();
    void loadSupComModel();
    void loadLandscapeModel();

    std::shared_ptr<Suthanus::Box>                   _landscape;
    std::shared_ptr<YolonaOss::GL::DrawableList>     _preDrawables;
    std::shared_ptr<YolonaOss::GL::DrawableList>     _postDrawables;
    std::shared_ptr<YolonaOss::Camera::CameraSystem> _cam;
    YolonaOss::GL::DrawSpecification*                _spec;
    std::shared_ptr<Protagonist>                     _protagonist;
    std::shared_ptr<ScriptAPI>                       _physicAPI;
    std::shared_ptr<Context>                         _context;
    std::shared_ptr<Suthanus::HeightMap> _land;
    bool _drawDebug = false;
    YolonaOss::Mesh* _mesh;
    YolonaOss::SupComGLMesh* _scMesh;
    std::shared_ptr< SupComModel> _modl;
    glm::mat4 _boneRot = glm::mat4(1.0);
  };
}