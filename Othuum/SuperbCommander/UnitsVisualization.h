#pragma once

#include "Units.h"
#include "AthanahCommonLib/SupCom/Gamedata/Gamedata.h"

namespace Athanah {
  class SupComModel;
  class SupComMeshRendererDef;
  struct SupComMesh;
}

namespace Superb {
  class UnitsVisualization {
  public:
    UnitsVisualization(Ahwassa::Window*, Athanah::Gamedata&, Units&);
    virtual ~UnitsVisualization() = default;

    void draw();
    void debugDraw();
  private:
    std::vector<std::shared_ptr<Athanah::SupComMesh>>            _meshes  ;
    std::unique_ptr<Athanah::SupComMeshRendererDef>              _renderer;
    Ahwassa::Window*   _window;
    Units&             _units;
    Athanah::Gamedata& _gamedata;
  };
}