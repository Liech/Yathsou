#pragma once

#include "AhwassaGraphicsLib/Drawables/Drawable.h"
#include "IyathuumCoreLib/BaseTypes/MultiDimensionalArray.h"
#include "IyathuumCoreLib/BaseTypes/Color.h"
#include <memory>
namespace Ahwassa
{
  class Mesh;
  class SupComGLMesh;
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
 
  class Fatboy : public Ahwassa::Drawable
  {
  public:
    Fatboy(Ahwassa::Window*);

    virtual void draw() override;
    void update();
  private:
    void initPhysic();
    void drawLandscape();
    void initEnemys();
    void loadLandscapeModel();

    std::shared_ptr<Suthanus::Box>                   _landscape;
    std::vector<std::shared_ptr<Ahwassa::Drawable>>  _preDrawables;
    std::vector<std::shared_ptr<Ahwassa::Drawable>>  _postDrawables;
    std::shared_ptr<Protagonist>                     _protagonist;
    std::shared_ptr<ScriptAPI>                       _physicAPI;
    std::shared_ptr<Context>                         _context;
    std::shared_ptr<Suthanus::HeightMap> _land;
    bool _drawDebug = false;
  };
}