#pragma once

#include "UnitsOld.h"
#include "AthanahCommonLib/SupCom/Gamedata/Gamedata.h"

namespace Athanah {
  class SupComModel;
  class SupComMeshRendererDef;
  struct SupComMesh;
}

namespace Superb {
  class UnitsVisualization {
  public:
    UnitsVisualization(Ahwassa::Window*, Athanah::Gamedata&, UnitsOld&);
    virtual ~UnitsVisualization() = default;

    void draw();
    void debugDraw(bool box, bool dirs);
  private:
    std::vector<std::shared_ptr<Athanah::SupComMesh>>            _meshes  ;
    std::unique_ptr<Athanah::SupComMeshRendererDef>              _renderer;
    Ahwassa::Window*   _window;
    UnitsOld&             _units;
    Athanah::Gamedata& _gamedata;
  };
}